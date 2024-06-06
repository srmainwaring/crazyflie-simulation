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
 * 
 * @file CrazyflieController.cc
 * A simple control plugin for Ignition Gazebo for controlling the motors
 * 
 */

#include "CrazyflieController.hh"

#include <gz/plugin/Register.hh>

#include <gz/msgs/actuators.pb.h>
#include "gz/sim/components/Actuators.hh"


using namespace crazyflie_controller;

GZ_ADD_PLUGIN(
    crazyflie_controller::CrazyflieController,
    gz::sim::System,
    crazyflie_controller::CrazyflieController::ISystemConfigure,
    crazyflie_controller::CrazyflieController::ISystemPreUpdate)

using namespace crazyflie_controller;

CrazyflieController::CrazyflieController()
{
}

CrazyflieController::~CrazyflieController()
{

}

void CrazyflieController::Configure(const gz::sim::Entity &_entity,
    const std::shared_ptr<const sdf::Element> &_sdf,
    gz::sim::EntityComponentManager &_ecm,
    gz::sim::EventManager &/*_eventMgr*/)
{
    this->model = gz::sim::Model(_entity);
      this->motorCommands.mutable_velocity()->Resize(
      4, 0);

  _ecm.CreateComponent(this->model.Entity(),
                      gz::sim::components::Actuators(this->motorCommands));

}

void CrazyflieController::PreUpdate(const gz::sim::UpdateInfo &_info,
    gz::sim::EntityComponentManager &_ecm)
{

  this->motorCommands.set_velocity(0, 3000);
  this->motorCommands.set_velocity(1, 3000);
  this->motorCommands.set_velocity(2, 3000);
  this->motorCommands.set_velocity(3, 3000);

  auto motorCommandsComponent =
      _ecm.Component<gz::sim::components::Actuators>(this->model.Entity());

  motorCommandsComponent->SetData(this->motorCommands, 
                    [](const gz::msgs::Actuators &, const gz::msgs::Actuators &){return false;});

  _ecm.SetChanged(this->model.Entity(), gz::sim::components::Actuators::typeId, gz::sim::ComponentState::PeriodicChange);

  ignmsg << "set motors" << std::endl;
}


