// Copyright (c) 2013-2016 Trillek contributors. See AUTHORS.txt for details
// Licensed under the terms of the LGPLv3. See licenses/lgpl-3.0.txt

#pragma once

#include <memory>
#include <queue>

#include "physics-system.hpp"
#include "vcomputer-system.hpp"
#include "event-queue.hpp"

namespace tec {
	extern double UPDATE_RATE;

	struct Controller;

	class Simulation final : public CommandQueue < Simulation >,
		public EventQueue<KeyboardEvent>, public EventQueue<MouseBtnEvent>,
		public EventQueue<MouseMoveEvent>, public EventQueue<MouseClickEvent> {
	public:
		Simulation() { }
		~Simulation() { }

		GameState Simulate(const double delta_time, const GameState& interpolated_state);

		PhysicsSystem& GetPhysicsSystem() {
			return this->phys_sys;
		}

		VComputerSystem& GetVComputerSystem() {
			return this->vcomp_sys;
		}

		void AddController(Controller* controller);

		void On(std::shared_ptr<KeyboardEvent> data);
		void On(std::shared_ptr<MouseBtnEvent> data);
		void On(std::shared_ptr<MouseMoveEvent> data);
		void On(std::shared_ptr<MouseClickEvent> data);
	private:
		PhysicsSystem phys_sys;
		VComputerSystem vcomp_sys;

		CommandList current_command_list;

		std::list<Controller*> controllers;
	};
}
