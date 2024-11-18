import os
import shutil
import sys

def find_headers(directory):
    headers = []
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.h'):
                headers.append(os.path.join(root, file))
    return headers

def copy_headers(headers, destination, use_path=True):
    for header in headers:
        # Create the destination path preserving the directory structure
        if use_path:
            dest_path = os.path.join(destination, os.path.relpath(header, start='src'))
        else:
            dest_path = os.path.join(destination, os.path.relpath(header, start='builddir/src'))
        os.makedirs(os.path.dirname(dest_path), exist_ok=True)
        shutil.copy2(header, dest_path)

def copy_libraries(source, destination):
    if not os.path.exists(destination):
        os.makedirs(destination)
    for file in os.listdir(source):
        if file.endswith('.so') or file.endswith('.a'):
            shutil.copy2(os.path.join(source, file), destination)

def copy_generated_headers(build_dir, destination):
    headers = find_headers(build_dir)
    for header in headers:
        shutil.copy2(header, destination)

def copy_json_directory(destination):
    json_dir = 'json'
    dest_path = os.path.join(destination, 'include/json')
    if os.path.exists(json_dir):
        shutil.copytree(json_dir, dest_path, dirs_exist_ok=True)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: install_libs.py <base_path>")
        sys.exit(1)

    base_path = sys.argv[1]

    base_headers = find_headers('src')
    copy_headers(base_headers, os.path.join(base_path, 'include/powder_toy/'))

    extra_headers = find_headers('builddir/src')
    copy_headers(extra_headers, os.path.join(base_path, 'include/powder_toy/'), False)

    # Update the source path for the libraries
    current_dir = os.getcwd()
    copy_libraries(os.path.join(current_dir, 'builddir'), os.path.join(base_path, 'libpath'))

    # Copy the json directory
    copy_json_directory(base_path)

    # Replace includes in all headers
    all_headers = base_headers + extra_headers

    for header in all_headers:
        print(header)
