//include "Ajisai.h"
//#include "godot_cpp/classes/engine.hpp"
//#include "godot_cpp/classes/node.hpp"
//#include "godot_cpp/classes/object.hpp"
//#include "godot_cpp/classes/sprite2d.hpp"
//#include "godot_cpp/core/memory.hpp"
//#include "util/debug.hpp"
//#include "util/engine.hpp"
//
//#include <godot_cpp/classes/time.hpp>
//
//Ajisai::Ajisai()
//{
//}
//void Ajisai::_bind_methods()
//{
//}
//void Ajisai::_ready()
//{
//	Time* time = Time::get_singleton();
//	int start = time->get_ticks_usec();
//	
//	Sprite2D* sprite = memnew_arr(Sprite2D, 100);
//
//	int end = time->get_ticks_usec();
//	pprint((end-start)/1000000.0);
//}
//void Ajisai::_notification(int notification)
//{
//	switch (notification)
//	{
//		case Object::NOTIFICATION_PREDELETE:
//			break;
//		case Node::NOTIFICATION_WM_CLOSE_REQUEST:
//			pprint("exi?");
//			break;
//	}
//}
//
//// nah doesnt call when its exited by hotkeys
//void Ajisai::_exit_tree()
//{
//	pprint("exited");
//}
//void Ajisai::build_services()
//{
//}
//void Ajisai::bind_services()
//{
//}
//SceneMenu::SceneMenu()
//{
//	// clearing the array doesnt delete the objects
//	SceneStateNormal* s = memnew(SceneStateNormal);
//	SceneStateAuto* sa = memnew(SceneStateAuto);
//	SceneStateFastForward* sf = memnew(SceneStateFastForward);
//	states.append(s);
//	states.append(sa);
//	states.append(memnew(SceneStateAuto));
//	pprint(states[0]);
//	pprint(states[1]);
//	pprint(states[2]);
//	pprint(sizeof(states[0]));
//	pprint(sizeof(states[1]));
//	pprint(sizeof(states[2]));
//	std::cout << &states[0] << std::endl;
//	std::cout << &states[1] << std::endl;
//	std::cout << &states[2] << std::endl;
//	std::cout << &s << std::endl;
//	std::cout << &sa << std::endl;
//	std::cout << &sf << std::endl;
//	std::cout << sizeof(states[0]) << std::endl;
//	pprint(sizeof(SceneStateFastForward));
//	pprint(sizeof(SceneStateAuto));
//	pprint(sizeof(SceneStateNormal));
//	pprint(sizeof(states));
//	pprint(sizeof(*s));
//	pprint(sizeof(*sa));
//	pprint(sizeof(*sf));
//	states.clear();
//	std::cout << s << std::endl;
//	std::cout << sa << std::endl;
//	std::cout << sf << std::endl;
//	std::cout << &s << std::endl;
//	std::cout << &sa << std::endl;
//	pprint(sa->to_string());
//	
//};
	// NOTE: clearing the array doesnt delete the objects
	// arrays in godot are just collection of pointers to objects gdi
	// cause memnew returns a pointer then storing that to array
	// brauh
	//
	// NOTE: only works in non-objects derived types
	// void* arr = memnew_arr(int,10);
	
	//SceneStateNormal* s = memnew(SceneStateNormal);
	//SceneStateAuto* sa = memnew(SceneStateAuto);
	//SceneStateFastForward* sf = memnew(SceneStateFastForward);
	//states.append(s);
	//states.append(sa);
	//states.append(sf);
	//SceneStates states_array[3];
	//int num[4];
	//num[0] = 9;
	//std::array<SceneStates*, 4> sta { memnew(SceneStateNormal), memnew(SceneStateNormal), 
	//	memnew(SceneStateNormal) };
	//std::cout << &sta << std::endl;
	//std::cout << sta[0] << std::endl;
	//std::cout << sta[1] << std::endl;
	//std::cout << sta[2] << std::endl;
	//std::cout << &sta[0] << std::endl;
	//std::cout << &sta[1] << std::endl;
	//std::cout << &sta[2] << std::endl;
	//std::cout << sizeof(*sta[0])<< std::endl;
	//std::cout << sizeof(&sta[0])<< std::endl;
	//pprint(sta[0]);

	//std::array<int, 5> num { 3, 4, 5, 6, };
	//std::cout << sizeof(&num[0])<< std::endl;
	//std::cout << sizeof(num[0])<< std::endl;
	//std::cout << &num << std::endl;
	//std::cout << num[0] << std::endl;
	//std::cout << num[1] << std::endl;
	//std::cout << num[2] << std::endl;
	//std::cout << num[3] << std::endl;
	//std::cout << &num[0] << std::endl;
	//std::cout << &num[1] << std::endl;
	//std::cout << &num[2] << std::endl;
	//std::cout << &num[3] << std::endl;

	//SceneStateNormal* s = memnew(SceneStateNormal);
	//SceneStateNormal* sf = memnew(SceneStateNormal);
	//SceneStateNormal* ss = memnew(SceneStateNormal);
	//TypedArray<SceneStates> gd[3];
	//gd->append(s);
	//gd->append(memnew(SceneStateNormal));
	//gd->append(memnew(SceneStateNormal));
	//std::cout << &gd[0] << std::endl;
	//std::cout << &gd[1] << std::endl;
	//std::cout << &gd[2] << std::endl;
	//std::cout << &s << std::endl;
	//std::cout << s << std::endl;
	//std::cout << sf << std::endl;
	//std::cout << ss << std::endl;
	//pprint(&gd[0]);
	//
	//memStates = (SceneStates*)memalloc(sizeof(SceneStates)*4);
	//
	//SceneStates* s = memnew_placement(&memStates[0], SceneStates);
	//memnew_placement(&memStates[1], SceneStates);
	//pprint(&memStates[1]);
	//pprint(&memStates[0]);
	//pprint(sizeof(&memStates));
	//pprint(sizeof(memStates[0]));
	//pprint(sizeof(memStates[1]));
	//pprint(memStates);
	//std::cout << &memStates[0] << std::endl;
	//std::cout << &memStates[1] << std::endl;

	//std::cout << &s << std::endl;
	//std::cout << s << std::endl;
	//
	////s->~SceneStates();
	//memdelete(s);
	//Node2D*  mem = (Node2D*)memalloc(sizeof(Node2D)*10);
	//memnew_placement(&mem[0], Node2D);
	//memnew_placement(&mem[2], Node2D);
	//std::cout << sizeof(*mem) << std::endl;
	//std::cout << sizeof(Node2D) << std::endl;
	//memfree(&mem[1]);
	//int cmd_idx = 0;
	//int cmd_tip = 9;

	//for (cmd_idx; cmd_idx < 9; )
	//{
	//	print_line(cmd_idx);
	//	if (cmd_idx == 5)
	//		break;
	//	cmd_idx ++;

	//}

	//for (cmd_idx; cmd_idx >= 0; cmd_idx --)
	//{
	//	if (cmd_idx == 5)
	//		continue;
	//	print_line(cmd_idx);
	//}
	//for (cmd_idx; cmd_idx >= 0; cmd_idx --)
	//{
	//	if (cmd_idx == 5)
	//		continue;
	//	print_line(cmd_idx);
	//}
