#include <godot_cpp/classes/node.hpp>
#include "godot_cpp/classes/wrapped.hpp"


using namespace godot;


class MemoryTest : public Node
{
	GDCLASS(MemoryTest, Node)

public:
	MemoryTest() = default;
	~MemoryTest() = default;

	void _ready() override
	{
		//int total_textures = 250;
		//Ref<CompressedTexture2D> texture = Ref<CompressedTexture2D>(memnew(CompressedTexture2D));
		//texture->load("wallpaper_SE1a.png");
		////void* mem = memalloc(sizeof(CompressedTexture2D)*250);
		//Sprite2D* tex = memnew_arr(Sprite2D, 250);
		//Sprite2D* sprt = memnew(Sprite2D);
		//sprt->set_texture(texture);
		//pprint(sizeof(&mem));
		//for ( int i = 0; i < total_textures; i++ )
		//{
		//	Sprite2D* text = &tex[i];
		//	text->set_texture(texture);
		//	pprint("textruing");
	}
	

private:
	static void _bind_methods(){};

};
