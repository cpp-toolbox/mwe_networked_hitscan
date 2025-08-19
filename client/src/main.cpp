#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>

// REMOVE this one day.
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <Jolt/Jolt.h>
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Physics/Character/CharacterVirtual.h>
#include <Jolt/Physics/Collision/CastResult.h>
#include <Jolt/Physics/Collision/RayCast.h>

#include "graphics/draw_info/draw_info.hpp"
#include "graphics/input_graphics_sound_menu/input_graphics_sound_menu.hpp"

#include "input/glfw_lambda_callback_manager/glfw_lambda_callback_manager.hpp"
#include "input/input_state/input_state.hpp"

#include "utility/fixed_frequency_loop/fixed_frequency_loop.hpp"
#include "utility/jolt_glm_type_conversions/jolt_glm_type_conversions.hpp"
#include "utility/unique_id_generator/unique_id_generator.hpp"
#include "utility/periodic_signal/periodic_signal.hpp"
#include "utility/logger/logger.hpp"
#include "utility/temporal_binary_switch/temporal_binary_switch.hpp"

#include "graphics/ui_render_suite_implementation/ui_render_suite_implementation.hpp"
#include "graphics/input_graphics_sound_menu/input_graphics_sound_menu.hpp"
#include "graphics/vertex_geometry/vertex_geometry.hpp"
#include "graphics/shader_standard/shader_standard.hpp"
#include "graphics/batcher/generated/batcher.hpp"
#include "graphics/shader_cache/shader_cache.hpp"
#include "graphics/fps_camera/fps_camera.hpp"
#include "graphics/window/window.hpp"
#include "graphics/colors/colors.hpp"
#include "graphics/ui/ui.hpp"

#include "system_logic/toolbox_engine/toolbox_engine.hpp"
#include "system_logic/physics/physics.hpp"
#include "system_logic/mouse_update_logger/mouse_update_logger.hpp"
#include "system_logic/hitscan_logic/hitscan_logic.hpp"

#include "networking/client_networking/network.hpp"
#include "networking/packet_handler/packet_handler.hpp"
#include "networking/packets/packets.hpp"

#include <iostream>
#include <format>

ConsoleLogger tick_logger{"tick"};

glm::vec2 get_ndc_mouse_pos1(GLFWwindow *window, double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);

    return {(2.0f * xpos) / width - 1.0f, 1.0f - (2.0f * ypos) / height};
}

glm::vec2 aspect_corrected_ndc_mouse_pos1(const glm::vec2 &ndc_mouse_pos, float x_scale) {
    return {ndc_mouse_pos.x * x_scale, ndc_mouse_pos.y};
}

class Hud3D {
  private:
    Batcher &batcher;
    InputState &input_state;
    Configuration &configuration;
    FPSCamera &fps_camera;
    UIRenderSuiteImpl &ui_render_suite;
    Window &window;

    const glm::vec3 crosshair_color = colors::green;

    const std::string crosshair = R"(
--*--
--*--
*****
--*--
--*--
)";

    vertex_geometry::Rectangle crosshair_rect = vertex_geometry::Rectangle(glm::vec3(0), 0.1, 0.1);

    draw_info::IVPColor crosshair_ivpsc;

    int crosshair_batcher_object_id;

  public:
    Hud3D(Configuration &configuration, InputState &input_state, Batcher &batcher, FPSCamera &fps_camera,
          UIRenderSuiteImpl &ui_render_suite, Window &window)
        : batcher(batcher), input_state(input_state), configuration(configuration), fps_camera(fps_camera),
          ui_render_suite(ui_render_suite), window(window), ui(create_ui()) {}

    ConsoleLogger logger;

    UI ui;
    int fps_ui_element_id, pos_ui_element_id;
    float average_fps;

    UI create_ui() {
        UI hud_ui(0, batcher.absolute_position_with_colored_vertex_shader_batcher.object_id_generator);
        fps_ui_element_id = hud_ui.add_textbox(
            "FPS", vertex_geometry::create_rectangle_from_top_right(glm::vec3(1, 1, 0), 0.2, 0.2), colors::black);
        pos_ui_element_id = hud_ui.add_textbox(
            "POS", vertex_geometry::create_rectangle_from_bottom_left(glm::vec3(-1, -1, 0), 0.8, 0.4), colors::black);

        crosshair_batcher_object_id =
            batcher.absolute_position_with_colored_vertex_shader_batcher.object_id_generator.get_id();
        auto crosshair_ivp = vertex_geometry::text_grid_to_rect_grid(crosshair, crosshair_rect);
        std::vector<glm::vec3> cs(crosshair_ivp.xyz_positions.size(), crosshair_color);
        crosshair_ivpsc = draw_info::IVPColor(crosshair_ivp, cs, crosshair_batcher_object_id);

        return hud_ui;
    }

    void process_and_queue_render_hud_ui_elements() {

        if (configuration.get_value("graphics", "show_pos").value_or("off") == "on") {
            ui.unhide_textbox(pos_ui_element_id);
            ui.modify_text_of_a_textbox(pos_ui_element_id, vec3_to_string(fps_camera.transform.get_translation()));
        } else {
            ui.hide_textbox(pos_ui_element_id);
        }

        if (configuration.get_value("graphics", "show_fps").value_or("off") == "on") {
            std::ostringstream fps_stream;
            fps_stream << std::fixed << std::setprecision(1) << average_fps;
            ui.modify_text_of_a_textbox(fps_ui_element_id, fps_stream.str());
            ui.unhide_textbox(fps_ui_element_id);
        } else {
            ui.hide_textbox(fps_ui_element_id);
        }

        auto ndc_mouse_pos =
            get_ndc_mouse_pos1(window.glfw_window, input_state.mouse_position_x, input_state.mouse_position_y);
        auto acnmp = aspect_corrected_ndc_mouse_pos1(ndc_mouse_pos, window.width_px / (float)window.height_px);

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            crosshair_batcher_object_id, crosshair_ivpsc.indices, crosshair_ivpsc.xyz_positions,
            crosshair_ivpsc.rgb_colors);

        process_and_queue_render_ui(acnmp, ui, ui_render_suite, input_state.get_just_pressed_key_strings(),
                                    input_state.is_just_pressed(EKey::BACKSPACE),
                                    input_state.is_just_pressed(EKey::ENTER),
                                    input_state.is_just_pressed(EKey::LEFT_MOUSE_BUTTON));
    }
};

void firing_logic(bool fire_just_pressed, ToolboxEngine &tbx_engine, JPH::Ref<JPH::CharacterVirtual> physics_target,
                  unsigned int last_received_game_update_number) {
    if (fire_just_pressed) {
        LogSection _(tick_logger, "firing logic");
        bool had_hit = run_hitscan_logic(tbx_engine.fps_camera, physics_target);
        auto hit_position = physics_target->GetPosition();

        if (had_hit) {
            tick_logger.debug("hit target lagun: {} at: {}, {}, {} with yaw, pitch {}, {}",
                              last_received_game_update_number, hit_position.GetX(), hit_position.GetY(),
                              hit_position.GetZ(), tbx_engine.fps_camera.transform.get_rotation_yaw(),
                              tbx_engine.fps_camera.transform.get_rotation_pitch());
            tbx_engine.sound_system.queue_sound(SoundType::CLIENT_HIT);
        } else {
            tick_logger.debug("missed target lagun: {} at: {}, {}, {} with yaw, pitch {}, {}\n",
                              last_received_game_update_number, hit_position.GetX(), hit_position.GetY(),
                              hit_position.GetZ(), tbx_engine.fps_camera.transform.get_rotation_yaw(),
                              tbx_engine.fps_camera.transform.get_rotation_pitch());
            tbx_engine.sound_system.queue_sound(SoundType::CLIENT_MISS);
        }
    }
}

// next step is this, instead of immediately setting the targets position, instead we wait until we have two game
// updates, we don't actually wait though, whatever the servers send rate is (put in shared and then distribute as
// constants file), then we take that period and double it and add some threshold, then we're almost always guarenteed
// to have 2 game updates loaded in, assume we do have two updates loaded in, then when we fire the gun, we have to
// figure out how far we are between those two updates, to do this as time progresses we interpolate between the two
// positions, and we can determine the value beteen 0 and 1 to see how far along we are. Once we know that we can
// package that in with the game update, and then send that to the server, and then we can rollback to that point and
// interpolate and then fire.
//
// How do we do it as we iterate in a tick we want to know how far we are between two updates, once we have two updates
// we immediately start some sort of timer, what if we have an iterating loop then and every 60hz period we load in the
// next game update, as we iterate we get a sub section of that time, and

int main() {

    // temporary badness
    std::unordered_map<SoundType, std::string> sound_type_to_file = {
        {SoundType::CLIENT_HIT, "assets/sounds/client_hit.wav"},
        {SoundType::CLIENT_MISS, "assets/sounds/client_miss.wav"},
        {SoundType::SERVER_HIT, "assets/sounds/server_hit.wav"},
        {SoundType::SERVER_MISS, "assets/sounds/server_miss.wav"},
        {SoundType::UI_HOVER, "assets/sounds/hover.wav"},
        {SoundType::UI_CLICK, "assets/sounds/click.wav"},
        {SoundType::UI_SUCCESS, "assets/sounds/success.wav"},
    };

    ToolboxEngine tbx_engine("mwe_networked_hitscan",
                             {ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX,
                              ShaderType::ABSOLUTE_POSITION_WITH_COLORED_VERTEX},
                             sound_type_to_file);

    PacketHandler packet_handler;
    Physics physics;

    MouseUpdateLogger mouse_update_logger;
    mouse_update_logger.logger.disable_all_levels();

    auto physics_target = physics.create_character(0);

    draw_info::IVPNColor target = draw_info::IVPNColor(
        vertex_geometry::generate_cylinder(8, physics.character_height_standing, physics.character_radius),
        colors::purple);

    // Network network("localhost", 7777);
    Network network("104.131.10.102", 7777);
    network.logger.disable_all_levels();
    network.initialize_network();
    network.attempt_to_connect_to_server();

    float room_size = 16.0f;

    tbx_engine.fps_camera.fov.add_observer([&](const float &new_value) {
        tbx_engine.shader_cache.set_uniform(
            ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX, ShaderUniformVariable::CAMERA_TO_CLIP,
            tbx_engine.fps_camera.get_projection_matrix(tbx_engine.window.width_px, tbx_engine.window.height_px));
    });

    struct LabelledMousePos {
        unsigned int mouse_pos_update_number;
        double x_pos;
        double y_pos;
    };

    unsigned int last_received_game_update_number = 0;
    std::vector<LabelledMousePos> mouse_pos_history;

    std::function<void(const void *)> game_update_handler = [&](const void *data) {
        LogSection _(tick_logger, "game update handler");
        const GameUpdatePacket *packet = reinterpret_cast<const GameUpdatePacket *>(data);
        GameUpdate just_received_game_update = packet->game_update;

        last_received_game_update_number = just_received_game_update.update_number;

        tick_logger.debug("just received game update");
        tick_logger.debug("last processed mouse update: {}",
                          just_received_game_update.last_processed_mouse_pos_update_number);

        auto predicted_yaw = tbx_engine.fps_camera.transform.get_rotation_yaw();
        auto predicted_pitch = tbx_engine.fps_camera.transform.get_rotation_pitch();

        tbx_engine.fps_camera.transform.set_rotation_pitch(just_received_game_update.pitch);
        tbx_engine.fps_camera.transform.set_rotation_yaw(just_received_game_update.yaw);

        tick_logger.debug("setting camera angle based on what server says | yaw: {} pitch: {} ",
                          tbx_engine.fps_camera.transform.get_rotation_yaw(),
                          tbx_engine.fps_camera.transform.get_rotation_pitch());

        glm::vec3 new_target_pos(just_received_game_update.target_x_pos, just_received_game_update.target_y_pos,
                                 just_received_game_update.target_z_pos);

        physics_target->SetPosition(g2j(new_target_pos));
        target.transform.set_translation(new_target_pos);

        tick_logger.debug("just updated the targets position to: {}", vec3_to_string(new_target_pos));

        // NOTE: we don't ever need to use updates that came before
        std::erase_if(mouse_pos_history, [&](const auto &lmp) {
            return lmp.mouse_pos_update_number < just_received_game_update.last_processed_mouse_pos_update_number;
        });

        tick_logger.start_section("reconciliation");
        tick_logger.debug("before reconciling our client simulated angles were yaw: {} pitch: {} ", predicted_yaw,
                          predicted_pitch);
        for (const auto &lmp : mouse_pos_history) {
            if (lmp.mouse_pos_update_number == just_received_game_update.last_processed_mouse_pos_update_number) {
                tick_logger.debug("set mouse position to the last processed one on the server: ({}, {})", lmp.x_pos,
                                  lmp.y_pos);
                tbx_engine.fps_camera.mouse.last_mouse_position_x = lmp.x_pos;
                tbx_engine.fps_camera.mouse.last_mouse_position_y = lmp.y_pos;
            } else if (lmp.mouse_pos_update_number > just_received_game_update.last_processed_mouse_pos_update_number) {
                tick_logger.debug("reapplying mouse position: ({}, {})", lmp.x_pos, lmp.y_pos);
                tbx_engine.fps_camera.mouse_callback(lmp.x_pos, lmp.y_pos);
                tick_logger.debug("resulting in yaw pitch: ({}, {})",
                                  tbx_engine.fps_camera.transform.get_rotation_yaw(),
                                  tbx_engine.fps_camera.transform.get_rotation_pitch());
            }
        }
        tick_logger.end_section("reconciliation");

        auto reconciled_yaw = tbx_engine.fps_camera.transform.get_rotation_yaw();
        auto reconciled_pitch = tbx_engine.fps_camera.transform.get_rotation_pitch();

        tick_logger.debug("cpsr yaw pitch deltas: ({}, {})", reconciled_yaw - predicted_yaw,
                          reconciled_pitch - predicted_pitch);
    };

    packet_handler.register_handler(PacketType::GAME_UPDATE, game_update_handler);

    std::function<void(const void *)> sound_update_handler = [&](const void *data) {
        const SoundUpdatePacket *packet = reinterpret_cast<const SoundUpdatePacket *>(data);
        SoundUpdate just_received_sound_update = packet->sound_update;
        tbx_engine.sound_system.queue_sound(just_received_sound_update.sound_to_play);
    };

    packet_handler.register_handler(PacketType::SOUND_UPDATE, sound_update_handler);

    unsigned int mouse_pos_update_number = 0;

    std::function<void(double, double)> mouse_pos_callback = [&](double xpos, double ypos) {
        LogSection _(tick_logger, "mouse pos callback");
        tbx_engine.fps_camera.mouse_callback(xpos, ypos);
        tick_logger.debug("after processing [{}]: ({}, {}) we produced yaw pitch: ({}, {})", mouse_pos_update_number,
                          xpos, ypos, tbx_engine.fps_camera.transform.get_rotation_yaw(),
                          tbx_engine.fps_camera.transform.get_rotation_pitch());
        tbx_engine.input_state.glfw_cursor_pos_callback(xpos, ypos);
        LabelledMousePos lmp(mouse_pos_update_number, xpos, ypos);
        mouse_pos_history.push_back(lmp);
        mouse_pos_update_number += 1;
    };

    tbx_engine.glfw_lambda_callback_manager.set_cursor_pos_callback(mouse_pos_callback);

    tbx_engine::register_input_graphics_sound_config_handlers(tbx_engine.configuration, tbx_engine.fps_camera,
                                                              tbx_engine.main_loop);

    UIRenderSuiteImpl ui_render_suite(tbx_engine.batcher);
    Hud3D hud(tbx_engine.configuration, tbx_engine.input_state, tbx_engine.batcher, tbx_engine.fps_camera,
              ui_render_suite, tbx_engine.window);
    InputGraphicsSoundMenu input_graphics_sound_menu(tbx_engine.window, tbx_engine.input_state, tbx_engine.batcher,
                                                     tbx_engine.sound_system, tbx_engine.configuration);

    PeriodicSignal send_mouse_updates_signal(60);

    // room [[

    std::vector<glm::vec3> cube_colors;
    cube_colors.reserve(24); // 6 faces × 4 vertices each

    std::array<glm::vec3, 6> face_colors = {
        colors::white, colors::white, colors::black, colors::black, colors::orange, colors::orange,
    };

    // assign each face color to its 4 corresponding vertices
    for (const auto &color : face_colors) {
        for (int i = 0; i < 4; ++i) {
            cube_colors.push_back(color);
        }
    }

    draw_info::IVPNColor room = draw_info::IVPNColor(vertex_geometry::generate_cube(room_size), cube_colors);

    // room ]]

    // tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_solid_color_shader_batcher.tag_id(torus);
    tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.tag_id(room);
    tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.tag_id(target);

    tbx_engine.shader_cache.set_uniform(
        ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX, ShaderUniformVariable::CAMERA_TO_CLIP,
        tbx_engine.fps_camera.get_projection_matrix(tbx_engine.window.width_px, tbx_engine.window.height_px));

    tbx_engine.shader_cache.set_uniform(ShaderType::ABSOLUTE_POSITION_WITH_COLORED_VERTEX,
                                        ShaderUniformVariable::ASPECT_RATIO,
                                        glm::vec2(tbx_engine.window.height_px / (float)tbx_engine.window.width_px, 1));

    TemporalBinarySignal fire_pressed_per_send_tbs;
    bool fire_pressed_since_last_send = false;
    bool fire_pressed_since_last_send_prev = false;

    bool use_subtick_firing = false;

    std::function<void(double)> tick = [&](double dt) {
        LogSection _(tick_logger, "tick");

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (send_mouse_updates_signal.process_and_get_signal()) {

            LogSection _(tick_logger, "sending mouse updates");

            bool fire_just_pressed_since_last_send =
                fire_pressed_since_last_send and not fire_pressed_since_last_send_prev;

            tick_logger.debug("fire_just_pressed_since_last_send: ", fire_just_pressed_since_last_send);

            // if (fire_pressed_since_last_send) {
            //     fire_pressed_per_send_tbs.set_on();
            // } else {
            //     fire_pressed_per_send_tbs.set_off();
            // }
            //

            if (not use_subtick_firing) {
                // we only allow firing here so you can't fire on subtick which can cause descrepancies between hits on
                // client and server
                firing_logic(fire_just_pressed_since_last_send, tbx_engine, physics_target,
                             last_received_game_update_number);
            }

            if (not mouse_pos_history.empty()) {

                LogSection _(tick_logger, "about to send the last mouse pos in history");

                auto last_mouse_pos = mouse_pos_history.back();

                tick_logger.debug("sending out mouse pos [{}]: ({}, {})", last_mouse_pos.mouse_pos_update_number,
                                  last_mouse_pos.x_pos, last_mouse_pos.y_pos);
                MouseUpdate mu(last_mouse_pos.mouse_pos_update_number, last_received_game_update_number,
                               last_mouse_pos.x_pos, last_mouse_pos.y_pos,
                               fire_pressed_since_last_send, // NOTE: we use this instead of sampling the keyboard now.
                               tbx_engine.fps_camera.active_sensitivity);
                MouseUpdatePacket mup;
                mup.header.type = PacketType::MOUSE_UPDATE;
                mup.header.size_of_data_without_header = sizeof(MouseUpdate);
                mup.mouse_update = mu;
                network.send_packet(&mup, sizeof(MouseUpdatePacket));
            }
            fire_pressed_since_last_send_prev = fire_pressed_since_last_send;
            fire_pressed_since_last_send = false;
        }

        std::vector<PacketWithSize> pws = network.get_network_events_received_since_last_tick();
        packet_handler.handle_packets(pws);

        // target.transform.set_translation();

        tbx_engine.shader_cache.set_uniform(
            ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX, ShaderUniformVariable::CAMERA_TO_CLIP,
            tbx_engine.fps_camera.get_projection_matrix(tbx_engine.window.width_px, tbx_engine.window.height_px));

        tbx_engine.shader_cache.set_uniform(ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX,
                                            ShaderUniformVariable::WORLD_TO_CAMERA,
                                            tbx_engine.fps_camera.get_view_matrix());

        tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.queue_draw(room);
        tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.queue_draw(target);

        tbx_engine::potentially_switch_between_menu_and_3d_view(tbx_engine.input_state, input_graphics_sound_menu,
                                                                tbx_engine.fps_camera, tbx_engine.window);

        hud.process_and_queue_render_hud_ui_elements();

        if (input_graphics_sound_menu.enabled) {
            input_graphics_sound_menu.process_and_queue_render_menu(tbx_engine.window, tbx_engine.input_state,
                                                                    ui_render_suite);
        } else {
            // tbx_engine::config_x_input_state_x_fps_camera_processing(tbx_engine.fps_camera, tbx_engine.input_state,
            //                                                          tbx_engine.configuration, dt);
        }

        if (use_subtick_firing) {
            // we only allow firing here so you can't fire on subtick which can cause descrepancies between hits on
            // client and server
            firing_logic(tbx_engine.input_state.is_just_pressed(EKey::LEFT_MOUSE_BUTTON), tbx_engine, physics_target,
                         last_received_game_update_number);
        }

        fire_pressed_since_last_send =
            fire_pressed_since_last_send or tbx_engine.input_state.is_pressed(EKey::LEFT_MOUSE_BUTTON);

        if (fire_pressed_since_last_send)
            tick_logger.debug("after processing ");

        // std::cout << "mouse update: " << mouse_pos_update_number << " fpsls: " <<
        // fire_pressed_since_last_send
        //           << std::endl;

        tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.upload_ltw_matrices();
        tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.draw_everything();
        tbx_engine.batcher.absolute_position_with_colored_vertex_shader_batcher.draw_everything();

        tbx_engine.sound_system.play_all_sounds();

        glfwSwapBuffers(tbx_engine.window.glfw_window);
        glfwPollEvents();

        // tick_logger.tick();

        TemporalBinarySignal::process_all();
    };

    std::function<bool()> termination = [&]() { return glfwWindowShouldClose(tbx_engine.window.glfw_window); };

    std::function<void(IterationStats)> loop_stats_function = [&](IterationStats is) {
        hud.average_fps = is.measured_frequency_hz;
    };

    tbx_engine.main_loop.start(tick, termination, loop_stats_function);

    return 0;
}
