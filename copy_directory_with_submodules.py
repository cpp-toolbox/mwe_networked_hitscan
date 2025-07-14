import os
import shutil
import subprocess
from pathlib import Path
import configparser

def get_repo_root():
    result = subprocess.run(['git', 'rev-parse', '--show-toplevel'],
                            stdout=subprocess.PIPE, text=True, check=True)
    return Path(result.stdout.strip())

def parse_gitmodules(repo_root):
    config = configparser.ConfigParser()
    gitmodules_path = repo_root / '.gitmodules'
    if not gitmodules_path.exists():
        return {}

    config.read(gitmodules_path)
    submodules = {}

    for section in config.sections():
        if not section.startswith("submodule"):
            continue
        path = config[section].get("path")
        url = config[section].get("url")
        if path and url:
            submodules[path] = url
    return submodules

def copy_directory_with_submodules(src, dst):
    repo_root = get_repo_root()
    submodules = parse_gitmodules(repo_root)

    src = Path(src).resolve()
    dst = Path(dst).resolve()

    submodules_to_add = []

    for root, dirs, files in os.walk(src):
        rel_root = Path(root).relative_to(src)
        dst_root = dst / rel_root

        # Check if any submodules exist at this level
        to_remove = []
        for d in dirs:
            full_path = (Path(root) / d).resolve()
            rel_path = full_path.relative_to(repo_root).as_posix()
            if rel_path in submodules:
                dst_submodule_path = (dst / rel_root / d).relative_to(repo_root)
                submodules_to_add.append((dst_submodule_path.as_posix(), submodules[rel_path]))
                to_remove.append(d)

        # Prevent os.walk from descending into submodules
        for d in to_remove:
            dirs.remove(d)

        # Copy files and dirs
        os.makedirs(dst_root, exist_ok=True)
        for f in files:
            src_file = Path(root) / f
            dst_file = dst_root / f
            shutil.copy2(src_file, dst_file)

    # Re-add submodules
    for rel_path, url in submodules_to_add:
        print(f"Adding submodule: {url} -> {rel_path}")
        subprocess.run(['git', 'submodule', 'add', url, rel_path], check=True)

    print("✅ Done.")

if __name__ == "__main__":
    import sys
    if len(sys.argv) != 3:
        print("Usage: python copy_directory_with_submodules.py <src> <dst>")
        sys.exit(1)

    copy_directory_with_submodules(sys.argv[1], sys.argv[2])
