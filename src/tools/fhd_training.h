#pragma once

#include <memory>
#include <mutex>
#include <thread>
#include <atomic>
#include <string>
#include <vector>

struct fhd_training {
  int max_epochs = 40000;
  int target_mse = 0.005f;
  std::atomic<bool> running = ATOMIC_VAR_INIT(false);
  std::atomic<int> epoch;
  std::thread training_thread;
  std::mutex access_lock;
  std::vector<float> errors = std::vector<float>(256, 0.f);
  std::string candidate_database_name = std::string(512, 0);
  std::array<char, 512> output_classifier_buf;
  std::string error;


  fhd_training();
  ~fhd_training();
};

bool fhd_training_start(fhd_training* t);
