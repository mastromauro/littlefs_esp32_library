#include <Arduino.h>
#include "FileHandler.hpp"
#include "esp_log.h"

const esp_vfs_littlefs_conf_t conf = {
  .base_path = "/littlefs",
  .partition_label = "storage",
  .format_if_mount_failed = false,
  .dont_mount = false,
};

FileHandler f = FileHandler(&conf);

char buf[128] = {0};

void read_cycle(){
  Serial.println(esp_err_to_name(f.OpenFile("test_info.txt", "r")));
  Serial.println(esp_err_to_name(f.ReadFile(buf, 128, 0)));
  Serial.print("Buffer: ");
  Serial.println(buf);
  Serial.println(esp_err_to_name(f.CloseFile()));
}

void write_cycle(){
  Serial.println(esp_err_to_name(f.OpenFile("test_info.txt", "w+")));
  Serial.println(esp_err_to_name(f.Write("Test string. Go crazy.")));
  // if you wish, you can read here too.
  Serial.println(esp_err_to_name(f.CloseFile()));
}

void setup() {
  Serial.begin(115200);
  //esp_littlefs_format("storage");
  f.Mount();
  write_cycle();
  read_cycle();
  f.Unmount();
}

void loop() {
  // put your main code here, to run repeatedly:
}
