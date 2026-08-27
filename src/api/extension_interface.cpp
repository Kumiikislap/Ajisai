#include <type_traits>

#include <gdextension_interface.h>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "api/extension_interface.hpp"
#include "features/movie/Actor.h"
#include "godot_cpp/core/class_db.hpp"
#include "main.h"
#include "main_menu.h"
#include "singletons/sglobal.h"
#include "util/engine.hpp"

#include "features/movie/ActorResource.h"
#include "features/movie/CharactersResource.h"
#include "features/movie/Director.h"
#include "services/DialogueManagerWrapper.h"
#include "features/movie/Actor.h"
#include "features/movie/ActorsLayer.h"
#include "features/movie/TweenAnimations.h"

namespace rl
{
    //static inline SGlobal* global_singleton{ nullptr };

    void initialize_static_objects()
    {
        //global_singleton = memnew(SGlobal);
        //rl::engine::get()->register_singleton("SGlobal", SGlobal::get_ins());
    }

    void teardown_static_objects()
    {
        //rl::engine::get()->unregister_singleton("SGlobal");
        //memdelete(global_singleton);
    }

    void initialize_extension_module(godot::ModuleInitializationLevel init_level)
    {
        if (init_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
            return;

        godot::ClassDB::register_runtime_class<Main>();
        godot::ClassDB::register_runtime_class<MainMenu>();
        //godot::ClassDB::register_class<SGlobal>();

		godot::ClassDB::register_runtime_class<ActorResource>();
		godot::ClassDB::register_runtime_class<CharactersResource>();
		godot::ClassDB::register_runtime_class<Director>();
		godot::ClassDB::register_runtime_class<DialogueManagerWrapper>();
		godot::ClassDB::register_runtime_class<Actor>();
		godot::ClassDB::register_runtime_class<ActorsLayer>();
		godot::ClassDB::register_runtime_class<TweenAnimations>();


        initialize_static_objects();
    }

    void uninitialize_extension_module(godot::ModuleInitializationLevel init_level)
    {
        if (init_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE)
            return;

        teardown_static_objects();
    }

    extern "C"
    {
        GDExtensionBool GDE_EXPORT extension_library_init(GDExtensionInterfaceGetProcAddress addr,
                                                          GDExtensionClassLibraryPtr lib,
                                                          GDExtensionInitialization* init)
        {
            const auto init_level = godot::MODULE_INITIALIZATION_LEVEL_SCENE;
            godot::GDExtensionBinding::InitObject init_obj(addr, lib, init);

            init_obj.register_initializer(initialize_extension_module);
            init_obj.register_terminator(uninitialize_extension_module);
            init_obj.set_minimum_library_initialization_level(init_level);

            return init_obj.init();
        }
    }
}
