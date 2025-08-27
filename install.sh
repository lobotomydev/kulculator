#!/bin/bash

ARCHIVE_URL="https://github.com/lobotomydev/kulculator/releases/download/1.0.0/kulkulator.tar.gz"
ARCHIVE_NAME="Kulculator.tar.gz"
UNPACK_DIR="kulculator"

check_curl() {
  if ! command -v curl &> /dev/null; then
    echo "Error: curl is not found. Please install it."
    exit 1
  fi
}

download_archive() {
  echo "Downloading archive..."
  curl -L "$ARCHIVE_URL" -o "$ARCHIVE_NAME"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to download the archive. Please check the URL."
    exit 1
  fi
  echo "Archive downloaded successfully."
}

unpack_archive() {
  echo "Unpacking archive..."
  tar -xzf "$ARCHIVE_NAME"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to unpack the archive."
    exit 1
  fi
  echo "Archive unpacked successfully."
}

install_to_system() {
  echo "Installing to system directories..."
  
  sudo cp "$UNPACK_DIR/bin/kulkulator" "/usr/bin/kulculator"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to copy the executable to /usr/bin. Administrator rights (sudo) may be required."
    exit 1
  fi
  echo "Executable successfully copied to /usr/bin."

  sudo cp "$UNPACK_DIR/share/applications/kulkulator.desktop" "/usr/share/applications/kulculator.desktop"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to copy the desktop file."
  fi
  
  sudo mkdir -p "/usr/share/icons/hicolor/128x128/apps/"
  sudo cp "$UNPACK_DIR/icons/hicolor/128x128/apps/Kulkulator_ds.png" "/usr/share/icons/hicolor/128x128/apps/kulculator_ds.png"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to copy the icon."
  fi
}

cleanup() {
  echo "Removing temporary files..."
  rm -rf "$UNPACK_DIR" "$ARCHIVE_NAME"
  echo "Done!"
}

check_curl
download_archive
unpack_archive
install_to_system
cleanup
echo "Kulculator installation succesfully completed"
