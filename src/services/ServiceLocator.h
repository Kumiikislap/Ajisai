#pragma once

#include <godot_cpp/classes/node.hpp>
#include "godot_cpp/classes/wrapped.hpp"

#include "services/DialogueManagerWrapper.h"

using namespace godot;

class ServiceLocator : public Node
{
   GDCLASS(ServiceLocator, Node);
	
   // TODO DialogueManagerWrapper interface
   static DialogueManagerWrapper* get_dialogue_manager()
   { return service; };

   static void provide(DialogueManagerWrapper* p_service)
   {
	   service = p_service;
   };

   private:
   static DialogueManagerWrapper* service;
};
