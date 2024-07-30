// Copyright (c) 2024，D-Robotics.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ELEVATION_NET_IMAGE_UTILS_H
#define ELEVATION_NET_IMAGE_UTILS_H

#include <memory>
#include <string>
#include <vector>

#include "dnn_node/dnn_node.h"

#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"

#define LOGE_AND_RETURN_IF_NULL(ptr)                   \
  if (ptr == nullptr) {                                \
    std::cerr << #ptr " is null pointer" << std::endl; \
    return;                                            \
  }

using hobot::dnn_node::DNNTensor;
using hobot::dnn_node::Model;
using hobot::dnn_node::ModelInferTask;
using hobot::dnn_node::NV12PyramidInput;

#define M_PI_F 3.141592653f

#define ALIGNED_2E(w, alignment) \
  ((static_cast<uint32_t>(w) + (alignment - 1U)) & (~(alignment - 1U)))
#define ALIGN_4(w) ALIGNED_2E(w, 4U)
#define ALIGN_8(w) ALIGNED_2E(w, 8U)
#define ALIGN_16(w) ALIGNED_2E(w, 16U)
#define ALIGN_64(w) ALIGNED_2E(w, 64U)

static cv::Scalar colors[] = {
    cv::Scalar(255, 0, 0),    // red
    cv::Scalar(255, 255, 0),  // yellow
    cv::Scalar(0, 255, 0),    // green
    cv::Scalar(0, 0, 255),    // blue
};

enum class ImageType { BGR = 0, NV12 = 1 };

class ImageUtils {
 public:
  int Init();
  int GetNV12Pyramid(const std::string &image_file, ImageType image_type,
                     int scaled_img_height, int scaled_img_width,
                     std::vector<std::shared_ptr<NV12PyramidInput>> &pym_list);

  int GetNV12Pyramid(const std::string &image_file, int scaled_img_height,
                     int scaled_img_width, int &original_img_height,
                     int &original_img_width,
                     std::vector<std::shared_ptr<NV12PyramidInput>> &pym_list);
  int GetNV12Pyramid(const cv::Mat &image, int scaled_img_height,
                     int scaled_img_width,
                     std::vector<std::shared_ptr<NV12PyramidInput>> &pym_list);

  int GetNV12PyramidFromNV12Img(
      const char *in_img_data, int in_img_height, int in_img_width,
      int scaled_img_height, int scaled_img_width,
      std::vector<std::shared_ptr<NV12PyramidInput>> &pym_list);

  int32_t BGRToNv12(cv::Mat &bgr_mat, cv::Mat &img_nv12);

 private:
  void FillTensorFromPym(std::shared_ptr<NV12PyramidInput> pym,
                         uint8_t *y_src_in, uint8_t *uv_src_in,
                         int32_t image_width, int32_t image_height);

  std::shared_ptr<NV12PyramidInput> NewNV12Pym(int32_t width, int32_t height);
  int FillTensor(std::shared_ptr<NV12PyramidInput> &pym,
                             uint8_t *y_src, uint8_t *uv_src);
  int CopyImagetoMat(uint8_t *y_src_in, uint8_t *uv_src_in,
                                 int32_t image_width, int32_t image_height);
  int CopyPymImageAlign(uint8_t *y_dst, uint8_t *uv_dst,
                                    uint8_t *y_src_in, uint8_t *uv_src_in,
                                    int32_t image_width, int32_t image_height);

 private:
  int model_input_height_ = 512, model_input_width_ = 960;
  cv::Mat Iw_t_1_;
  bool single_mode_ = false;

  void BilinearSampler(cv::Mat &img, const cv::Mat &grid, cv::Mat &warped_img);

  void SetIdGrid();
  cv::Mat H_;
  cv::Mat current_pixel_coords_;
  void WarpImage(cv::Mat &img, cv::Mat &warped_img);
  void Nv12ToRGB(cv::Mat &nv_img, cv::Mat &img);
  void RGBToNv12(cv::Mat &rgb_img, cv::Mat &nv_img);
  void WarpImageOpenCv(cv::Mat &img, cv::Mat &warped_img);
};

#endif  // ELEVATION_NET_IMAGE_UTILS_H
