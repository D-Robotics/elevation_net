// Copyright (c) 2021 Horizon Robotics.All Rights Reserved.
//
// The material in this file is confidential and contains trade secrets
// of Horizon Robotics Inc. This is proprietary information owned by
// Horizon Robotics Inc. No part of this work may be disclosed,
// reproduced, copied, transmitted, or used in any way for any purpose,
// without the express written permission of Horizon Robotics Inc.

#ifndef DNN_ELEVATION_NET_OUTPUT_PARSER_H
#define DNN_ELEVATION_NET_OUTPUT_PARSER_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "dnn/hb_dnn_ext.h"
#include "easy_dnn/data_structure.h"
#include "easy_dnn/description.h"
#include "easy_dnn/model.h"
#include "easy_dnn/output_parser.h"

using hobot::easy_dnn::DNNResult;
using hobot::easy_dnn::DNNTensor;
using hobot::easy_dnn::InputDescription;
using hobot::easy_dnn::Model;
using hobot::easy_dnn::MultiBranchOutputParser;
using hobot::easy_dnn::OutputDescription;
using hobot::easy_dnn::OutputParser;
using hobot::easy_dnn::SingleBranchOutputParser;

class ElevationNetOutputDescription : public OutputDescription {
 public:
  ElevationNetOutputDescription(Model *mode, int index, std::string type = "")
      : OutputDescription(mode, index, type) {}
  int op_type;
};

/**
 * \~Chinese @brief 单精度浮点数组，可用于存储特征值、质量结果等
 */
struct FloatArray {
  std::vector<float> values;
  /// \~Chinese 置信度
  float score = 0.0;
};

class ElevationNetResult : public DNNResult {
 public:
  FloatArray depth_result;
  FloatArray height_result;
};

class ElevationNetOutputParser : public SingleBranchOutputParser<ElevationNetResult> {
 public:
  int32_t Parse(
      std::shared_ptr<ElevationNetResult> &output,
      std::vector<std::shared_ptr<InputDescription>> &input_descriptions,
      std::shared_ptr<OutputDescription> &output_description,
      std::shared_ptr<DNNTensor> &output_tensor);

 private:
  int32_t PostProcess(std::shared_ptr<DNNTensor> &output_tensor,
                      std::shared_ptr<ElevationNetResult> &det_result);

 private:
  struct CameraParameter {
    float fx_inv_ = 0.0006045482782860858f, fy_inv_ = 0.0006044447633990631f;
    float cx_inv_ = -0.6043894145811973f, cy_inv_ = -0.3181318317406348f;
    float nx_ = 0.f, ny_ = 0.f, nz_ = 1.f;
    float cam_H_ = 1.f;
  };
  CameraParameter desc_;
  std::vector<float> points_;
  int model_output_height_, model_output_width_;

  int GetFrameOutPut_NEON(uint32_t shift, uint32_t src_w_stride,
                          void *depth_ptr, void *height_ptr, void *gamma_ptr);

  int GetFrameOutPut(uint32_t shift, uint32_t src_w_stride, void *depth_ptr,
                     void *height_ptr, void *gamma_ptr);
  void GenerateFeaturePoints(int width, int height);
};

#endif  // DNN_ELEVATION_NET_OUTPUT_PARSER_H
