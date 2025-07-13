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

#include "utility/unique_id_generator/unique_id_generator.hpp"
#include "utility/logger/logger.hpp"

#include <iostream>

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

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class SphereOrbitGenerator {
  public:
    // Constructor with default values for all parameters
    SphereOrbitGenerator(glm::vec3 center = glm::vec3(0.0f), float radius = 1.0f,
                         glm::vec3 travel_axis = glm::vec3(0.0f, 1.0f, 0.0f),
                         float angular_speed_rad_per_sec = glm::radians(90.0f), float initial_angle = 0.0f)
        : center(center), radius(radius), angular_speed(angular_speed_rad_per_sec), angle(initial_angle) {
        this->travel_axis = glm::normalize(travel_axis);

        set_travel_axis(travel_axis);
    }

    // Advance the orbit and return the new position
    glm::vec3 process(float dt) {
        angle += angular_speed * dt;
        glm::vec3 rotated = glm::rotate(orbit_vector, angle, travel_axis);
        return center + rotated;
    }

    void set_travel_axis(const glm::vec3 &travel_axis) {
        this->travel_axis = travel_axis;
        // Choose arbitrary initial vector orthogonal to travel_axis
        glm::vec3 fallback = glm::vec3(0.0f, 1.0f, 0.0f);
        if (glm::abs(glm::dot(fallback, this->travel_axis)) > 0.99f)
            fallback = glm::vec3(1.0f, 0.0f, 0.0f);

        orbit_vector = glm::normalize(glm::cross(travel_axis, fallback)) * radius;
    }

    void set_radius(const float &radius) { this->radius = radius; }
    void set_angular_speed(const float &angular_speed) { this->angular_speed = angular_speed; }

  private:
    glm::vec3 center;
    float radius;
    glm::vec3 travel_axis;
    glm::vec3 orbit_vector;
    float angle;
    float angular_speed;
};

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp> // for pi
#include <random>
#include <cmath>

// Returns a random float in the range [min, max)
float random_float(float min, float max) {
    static std::random_device rd;  // seed
    static std::mt19937 gen(rd()); // mersenne twister engine
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

// Generate a random unit vector in 3D
glm::vec3 random_unit_vector() {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    // Uniform distribution for azimuth angle [0, 2π)
    std::uniform_real_distribution<float> dist_azimuth(0.0f, 2.0f * glm::pi<float>());

    // Uniform distribution for z = cos(theta), to ensure uniform sphere distribution
    std::uniform_real_distribution<float> dist_z(-1.0f, 1.0f);

    float z = dist_z(gen);
    float azimuth = dist_azimuth(gen);
    float r = std::sqrt(1.0f - z * z);
    float x = r * std::cos(azimuth);
    float y = r * std::sin(azimuth);

    return glm::vec3(x, y, z);
}

int main() {

    ToolboxEngine tbx_engine("mwe_networked_hitscan", {ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX,
                                                       ShaderType::ABSOLUTE_POSITION_WITH_COLORED_VERTEX});

    Physics physics;

    float room_size = 16.0f;

    SphereOrbitGenerator sog(glm::vec3(0.0f, 1, 0), room_size / 2, glm::vec3(0.0f, 1.0f, 0.0f), glm::radians(90.0f),
                             0.0f);

    tbx_engine.fps_camera.fov.add_observer([&](const float &new_value) {
        tbx_engine.shader_cache.set_uniform(
            ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX, ShaderUniformVariable::CAMERA_TO_CLIP,
            tbx_engine.fps_camera.get_projection_matrix(tbx_engine.window.width_px, tbx_engine.window.height_px));
    });

    tbx_engine::register_input_graphics_sound_config_handlers(tbx_engine.configuration, tbx_engine.fps_camera,
                                                              tbx_engine.main_loop);

    UIRenderSuiteImpl ui_render_suite(tbx_engine.batcher);
    Hud3D hud(tbx_engine.configuration, tbx_engine.input_state, tbx_engine.batcher, tbx_engine.fps_camera,
              ui_render_suite, tbx_engine.window);
    InputGraphicsSoundMenu input_graphics_sound_menu(tbx_engine.window, tbx_engine.input_state, tbx_engine.batcher,
                                                     tbx_engine.sound_system, tbx_engine.configuration);

    GLFWLambdaCallbackManager glcm = tbx_engine::create_default_glcm_for_input_and_camera(
        tbx_engine.input_state, tbx_engine.fps_camera, tbx_engine.window, tbx_engine.shader_cache);

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

    auto physics_target = physics.create_character(0);

    draw_info::IVPNColor target = draw_info::IVPNColor(
        vertex_geometry::generate_cylinder(8, physics.character_height_standing, physics.character_radius),
        colors::purple);

    // tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_solid_color_shader_batcher.tag_id(torus);
    tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.tag_id(room);
    tbx_engine.batcher.cwl_v_transformation_ubos_1024_with_colored_vertex_shader_batcher.tag_id(target);

    tbx_engine.shader_cache.set_uniform(
        ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX, ShaderUniformVariable::CAMERA_TO_CLIP,
        tbx_engine.fps_camera.get_projection_matrix(tbx_engine.window.width_px, tbx_engine.window.height_px));

    tbx_engine.shader_cache.set_uniform(ShaderType::ABSOLUTE_POSITION_WITH_COLORED_VERTEX,
                                        ShaderUniformVariable::ASPECT_RATIO,
                                        glm::vec2(tbx_engine.window.height_px / (float)tbx_engine.window.width_px, 1));

    ConsoleLogger tick_logger;
    tick_logger.disable_all_levels();
    std::function<void(double)> tick = [&](double dt) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tbx_engine.shader_cache.set_uniform(
            ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX, ShaderUniformVariable::CAMERA_TO_CLIP,
            tbx_engine.fps_camera.get_projection_matrix(tbx_engine.window.width_px, tbx_engine.window.height_px));

        tbx_engine.shader_cache.set_uniform(ShaderType::CWL_V_TRANSFORMATION_UBOS_1024_WITH_COLORED_VERTEX,
                                            ShaderUniformVariable::WORLD_TO_CAMERA,
                                            tbx_engine.fps_camera.get_view_matrix());

        auto new_pos = sog.process(dt);
        target.transform.set_translation(new_pos);
        physics_target->SetPosition(g2j(new_pos));

        // hitscan logic [[

        if (tbx_engine.input_state.is_just_pressed(EKey::LEFT_MOUSE_BUTTON)) {
            JPH::RayCastResult rcr;
            JPH::RayCast aim_ray;
            aim_ray.mOrigin = JPH::Vec3(0, 0, 0);
            aim_ray.mDirection = g2j(tbx_engine.fps_camera.transform.compute_forward_vector()) * 100;
            aim_ray.mOrigin -= physics_target->GetPosition();
            bool hit = physics_target->GetShape()->CastRay(aim_ray, JPH::SubShapeIDCreator(), rcr);
            if (hit) {
                std::cout << "hit target" << std::endl;
                tbx_engine.sound_system.queue_sound(SoundType::UI_CLICK);
                sog.set_travel_axis(random_unit_vector());
                sog.set_radius(random_float(room_size / 4, room_size / 2));
                sog.set_angular_speed(random_float(glm::radians(45.0f), glm::radians(180.0f)));
            }
        }

        // hitscan logic ]]

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
