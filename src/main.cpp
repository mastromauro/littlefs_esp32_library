#include <Arduino.h>
#include "FileHandler.hpp"
#include "esp_log.h"

const esp_vfs_littlefs_conf_t conf = {
  .base_path = "/littlefs",
  .partition_label = "storage",
  .format_if_mount_failed = true,
  .dont_mount = false,
};

FileHandler f = FileHandler(&conf);

char buf[128] = {0};

void setup() {
  Serial.begin(115200);
  //esp_log_set_vprintf(new_vfprintf);
  esp_littlefs_format("storage");
  f.Mount();
  Serial.println(esp_err_to_name(f.CreateFile("file.txt")));
  Serial.println(esp_err_to_name(f.Write("AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH!")));
  f.ReadFile(buf, 0);
  Serial.print("Buffer: ");
  Serial.println(buf);
  f.Unmount();
}

void loop() {
  // put your main code here, to run repeatedly:
}
