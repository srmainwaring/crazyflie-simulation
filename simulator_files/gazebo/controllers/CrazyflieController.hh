/** 
 *  ...........       ____  _ __
 *  |  ,-^-,  |      / __ )(_) /_______________ _____  ___
 *  | (  O  ) |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 *  | / ,..´  |    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *     +.......   /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *  
 * MIT License
 * 
 * Copyright (c) 2022 Bitcraze
 * 
 * @file CrazyflieController.hh
 * Header file for CrazyflieController.cc
 * 
 */

#ifndef SYSTEM_PLUGIN_CRAZYFLIECONTROLLER_HH_
#define SYSTEM_PLUGIN_CRAZYFLIECONTROLLER_HH_

#include <gz/sim/System.hh>
#include <memory>
#include <string>
#include <gz/msgs.hh>
#include <gz/sim/components/Component.hh>
#include <gz/sim/config.hh>
#include "gz/sim/Model.hh"

namespace crazyflie_controller
{
  class CrazyflieController:
    public gz::sim::System,
    public gz::sim::ISystemConfigure,
    public gz::sim::ISystemPreUpdate
  {
    public: CrazyflieController();

    public: ~CrazyflieController() override;

    public: void Configure(const gz::sim::Entity &_entity,
                         const std::shared_ptr<const sdf::Element> &,
                         gz::sim::EntityComponentManager &_ecm,
                         gz::sim::EventManager &) override;

    public: void PreUpdate(const gz::sim::UpdateInfo &_info,
                gz::sim::EntityComponentManager &_ecm) override;

    private: gz::msgs::Actuators motorCommands;
    private: gz::sim::Model model{gz::sim::kNullEntity};

  };
}
//! [header]

#endif
