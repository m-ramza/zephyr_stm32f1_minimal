
unset ZEPHYR_BASE
pip3 install --user -r ../zephyr/scripts/requirements.txt
west update
west build -p auto --build-dir build . -- -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DBUILD_DOC=0

# -t guiconfig