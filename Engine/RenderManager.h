#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "Object.h"
#include "SDL.h"

#include <../glm/glm.hpp>
#include <../glm/gtc/matrix_transform.hpp>
#include <../glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H  


class RenderManager
{
public:
	//Get instance
	static RenderManager* GetRenderManager();
	//Create Render Manager
	void CreateRendermanager(SDL_Window* window);
	//Constructor
	RenderManager(SDL_Window* window);
	//Destructor
	~RenderManager();

	//render objects
	void RenderObjects(std::vector<Object*> objectsToRender);

	//creates a texture 
	void LoadTexture(std::string filePath);

	//Sets the sizes of receiving image
	void GetImageSize(Image* img);

private:
	//my instance
	static RenderManager* instance;

	int windowHeight;
	int windowWidth;

	//stores the texture width by is object
	std::unordered_map<std::string, int> textureWidth;
	//stores the texture hight by is object
	std::unordered_map<std::string, int> textureHeight;

	std::unordered_map<std::string, bool> hasTextureCreated;
	std::unordered_map<std::string, int> textureID;
	std::unordered_map<std::string, unsigned int> textureMap;

	int textureIDCounter = 0;

	unsigned int shaderProgram;
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;


	unsigned int textShaderProgram;

	FT_Library ft;
	FT_Face face;



	struct Character {
		unsigned int TextureID;  // ID handle of the glyph texture
		glm::ivec2   Size;       // Size of glyph
		glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
		unsigned int Advance;    // Offset to advance to next glyph
	};

	std::map<char, Character> Characters;


	SDL_GLContext context;
	SDL_Window* window;



};