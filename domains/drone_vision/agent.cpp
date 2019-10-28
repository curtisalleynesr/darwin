// Copyright 2019 The Darwin Neuroevolution Framework Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "agent.h"
#include "scene.h"

namespace drone_vision {

Agent::Agent(const darwin::Genotype* genotype, Scene* scene)
    : scene_(scene), brain_(genotype->grow()) {}

void Agent::simStep() {
  const auto& config = scene_->domain()->config();

  // setup inputs
  const auto camera = scene_->camera();
  const auto image = camera->render();
  CHECK(image.size() == config.camera_resolution);
  int input_index = 0;
  for (const auto& receptor : image) {
    brain_->setInput(input_index++, receptor.color.r);
    brain_->setInput(input_index++, receptor.color.g);
    brain_->setInput(input_index++, receptor.color.b);
    if (config.camera_depth) {
      brain_->setInput(input_index++, receptor.depth);
    }
  }

  brain_->think();

  // actions based on the output values
  scene_->moveDrone(b2Vec2(brain_->output(0), brain_->output(1)));
  scene_->rotateDrone(brain_->output(2));
}

int Agent::inputs(const Config& config) {
  return config.camera_resolution * (config.camera_depth ? 4 : 3);
}

int Agent::outputs(const Config&) {
  return 3;
}

}  // namespace drone_vision
