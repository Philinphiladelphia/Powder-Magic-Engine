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

def copy_headers(headers, destination):
    for header in headers:
        # Create the destination path preserving the directory structure
        dest_path = os.path.join(destination, os.path.relpath(header, start='src'))
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

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: install_libs.py <base_path>")
        sys.exit(1)

    base_path = sys.argv[1]

    headers = find_headers('src')
    copy_headers(headers, os.path.join(base_path, 'include/powder_toy/'))


    # Update the source path for the libraries
    current_dir = os.getcwd()
    copy_libraries(os.path.join(current_dir, 'builddir'), os.path.join(base_path, 'lib'))

    copy_generated_headers('build/src', os.path.join(base_path, 'include/powder_toy/'))

    for header in headers:
        print(header)