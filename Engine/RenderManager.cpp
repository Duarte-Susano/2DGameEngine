#include "RenderManager.h"
#include "SDL.h"
#include <algorithm>

#include <iostream>
#include <SDL.h>
#include <glad.h>

#include  "stb_image.h"


RenderManager* RenderManager::GetRenderManager()
{
	if (!instance)
		throw std::invalid_argument("Render Manager");
	return instance;
}

void RenderManager::CreateRendermanager(SDL_Window* window)
{
	instance = new RenderManager(window);
}

RenderManager::RenderManager(SDL_Window* rhsWindow)
{

	window = rhsWindow;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	//initialize glad context
	context = SDL_GL_CreateContext(window);
	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		SDL_Quit();
	}


	// Create the VERTEX SHADER to set the vertex positions 
	const char* vertexShaderSource = R"glsl(
	#version 330 core

    in vec2 position;
    in vec3 color;
    in vec2 texCoord;

    out vec3 Color;
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;


	void main()
	{
        gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
        Color = color;
        TexCoord = texCoord;
	}
	)glsl"; // Created a string that will later be translated

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); // Creates the shader to be used
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLint success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}




	//Create the Fragment Shader 
	const char* fragmentShaderSource = R"glsl(
	#version 330 core

    in vec3 Color;
    in vec2 TexCoord;

    out vec4 FragColor;

    uniform sampler2D textureSampler;

    void main()
    {
    vec4 colTex = texture(textureSampler, TexCoord);

	if(colTex.x >= 0.9f && colTex.y <= 0.1f && colTex.z >= 0.9f)
	{
		colTex.w = 0.0;
	}

	FragColor = colTex * vec4(Color, 1.0);
	}

	)glsl"; // Created a string that will later be translated

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);   // Creates the shader to be used
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	shaderProgram = glCreateProgram(); // Created an empty program 

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader); // Attach the shaders to the empty program
	glLinkProgram(shaderProgram); // Link the program and generate the shader program


	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//--------------------------------------------------------------------------------
	
	// Create the VERTEX SHADER to set the vertex positions 
	const char* textVertexShaderSource = R"glsl(
	#version 330 core

    in vec2 position;
    in vec3 color;
    in vec2 texCoord;

    out vec3 Color;
    out vec2 TexCoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 proj;

	void main()
	{
        gl_Position = proj * view * model * vec4(position, 0.0, 1.0);
        Color = color;
        TexCoord = texCoord;
	}
	)glsl"; // Created a string that will later be translated

	GLuint textVertexShader = glCreateShader(GL_VERTEX_SHADER); // Creates the shader to be used
	glShaderSource(textVertexShader, 1, &textVertexShaderSource, NULL);
	glCompileShader(textVertexShader);

	GLint textSuccess;
	char textInfoLog[512];
	glGetShaderiv(textVertexShader, GL_COMPILE_STATUS, &textSuccess);

	if (!textSuccess)
	{
		glGetShaderInfoLog(textVertexShader, 512, NULL, textInfoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << textInfoLog << std::endl;
		SDL_GL_DeleteContext(context);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	//Create the Fragment Shader 
	const char* textFragmentShaderSource = R"glsl(
	#version 330 core

    in vec3 Color;
    in vec2 TexCoord;

    out vec4 FragColor;

    uniform sampler2D textureSampler;

    void main()
    {
	vec4 colTex = vec4(1.0, 1.0, 1.0, texture(textureSampler, TexCoord).r);

    FragColor = colTex;
    }

	)glsl"; // Created a string that will later be translated

	GLuint textFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);   // Creates the shader to be used
	glShaderSource(textFragmentShader, 1, &textFragmentShaderSource, NULL);
	glCompileShader(textFragmentShader);
	glGetShaderiv(textFragmentShader, GL_COMPILE_STATUS, &textSuccess);

	if (!textSuccess)
	{
		glGetShaderInfoLog(textFragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	textShaderProgram = glCreateProgram(); // Created an empty program 

	glAttachShader(textShaderProgram, textVertexShader);
	glAttachShader(textShaderProgram, textFragmentShader); // Attach the shaders to the empty program
	glLinkProgram(textShaderProgram); // Link the program and generate the shader program


	glGetProgramiv(textShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(textShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
	}


	glDeleteShader(textVertexShader);
	glDeleteShader(textFragmentShader);

	
	
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}
	if (FT_New_Face(ft, "BebasNeue-Regular.ttf", 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	}

	FT_Set_Pixel_Sizes(face, 0,24);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

	for (unsigned char c = 0; c < 255; ++c)
	{

		// load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		}
		// generate texture
		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		// now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		++textureIDCounter;
		Characters.insert(std::pair<char, Character>(c, character));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
}

RenderManager::~RenderManager()
{
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	textureWidth.clear();
	textureHeight.clear();
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vao);

}


void RenderManager::RenderObjects(std::vector<Object*> objectsToRender)
{


	//vector with a pair refering to the Object and is layer
	std::vector<std::pair<Image, int> > layerVector;

	int objectsCounter = 0;


	//put in orderedObjects all objects that have an image to render
	for (int i = 0; i < objectsToRender.size(); i++)
	{
		if (objectsToRender[i]->HasComponent<Image>())
		{
			std::vector<Image*> objectImages;
			objectImages = objectsToRender[i]->GetComponents<Image>();

			for (int i = 0; i < objectImages.size(); i++)
			{
				Image image = *objectImages[i];
				if (image.isVisible && image.filePath != "")
				{
					//if the object has an image then it is add to the layer vector

					std::pair<Image, int> objWithTexture;
					objWithTexture.first = image;
					objWithTexture.second = image.layer;

					layerVector.push_back(objWithTexture);
				}
			}
		}
	}

	//Sorting the layerVector by the layers
	std::sort(layerVector.begin(), layerVector.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});
	

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);   //give to the window a color
	glClear(GL_COLOR_BUFFER_BIT);


	for (std::pair<Image, int> pair: layerVector)
	{

		++objectsCounter;
		Image renderImage = pair.first;
		std::string filePath = renderImage.filePath;


		LoadTexture(filePath);
		glBindTexture(GL_TEXTURE_2D, textureID[filePath]);
		glActiveTexture(GL_TEXTURE0);

		float nc = renderImage.nColumns;
		float fc = renderImage.framePositionColumn;
		float nr = renderImage.nRows;
		float fr = renderImage.framePositionRow;

		// X

		float rightVertices = 1 / nc * fc;

		float leftVertices = rightVertices - 1 / nc;

		// Y

		float bottomVertices = (1 / nr) * fr;

		float topVertices = bottomVertices + 1/ nr;


		//std::cout << renderImage.framePositionRow << std::endl;

		float r = renderImage.color.x;
		float g = renderImage.color.y;
		float b = renderImage.color.z;

		float vertices[] = {
		//position		color				textcoords
		0.5f, 0.5f,     r, g, b,  rightVertices, bottomVertices,
		0.5f, -0.5f,    r, g, b,  rightVertices, topVertices,
		-0.5f, -0.5f,   r, g, b,  leftVertices, topVertices,
		-0.5f, 0.5f,    r, g, b,  leftVertices, bottomVertices
		};
		unsigned int indices[] = { // note that we start from 0!
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
		};


		glm::mat4 model(1.0f);

		glm::mat4 view(1.0f);

		view = glm::translate(view, glm::vec3(0.f, 0.f, -3.f));

		
		//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

		float fWindowWidth = windowWidth;
		float fWindowHeight = windowHeight;
		glm::mat4 proj = glm::ortho(0.0f, fWindowWidth, 0.0f, fWindowHeight, 0.0f, 100.0f);
		

		if (renderImage.fullScreen)
		{
			model = glm::translate(model, glm::vec3(
				windowWidth / 2,
				windowHeight / 2,
				0));


			model = glm::scale(model, glm::vec3(
				windowWidth,
				windowHeight,
				0));

			model = glm::rotate(model, glm::radians(renderImage.myObject->GetComponent<Transform>().rotation.z), glm::vec3(0, 0, 1));
		}
		else if (renderImage.myObject->GetComponent<Transform>().parent != nullptr)
		{
			model = glm::translate(model, glm::vec3(
				((renderImage.myObject->GetComponent<Transform>().parent->position.x) +
				(renderImage.myObject->GetComponent<Transform>().position.x)),
				((renderImage.myObject->GetComponent<Transform>().parent->position.y) +
				(renderImage.myObject->GetComponent<Transform>().position.y)),
				0));

			model = glm::scale(model, glm::vec3(
				renderImage.myObject->GetComponent<Transform>().scale.x +
				renderImage.myObject->GetComponent<Transform>().parent->scale.x +
				renderImage.xOffSet,
				renderImage.myObject->GetComponent<Transform>().scale.y +
				renderImage.myObject->GetComponent<Transform>().parent->scale.y +
				renderImage.yOffSet,
				0));

			model = glm::rotate(model, glm::radians(renderImage.myObject->GetComponent<Transform>().rotation.z +
				renderImage.myObject->GetComponent<Transform>().parent->rotation.z), glm::vec3(0, 0, 1));
		}
		else
		{
			model = glm::translate(model, glm::vec3(
					(renderImage.myObject->GetComponent<Transform>().position.x) + renderImage.xOffSet,
					(renderImage.myObject->GetComponent<Transform>().position.y) + renderImage.yOffSet,
					0));

			model = glm::scale(model, glm::vec3(
				(textureWidth[filePath]/renderImage.nColumns) * (renderImage.myObject->GetComponent<Transform>().scale.x),
				(textureHeight[filePath]/renderImage.nRows) * (renderImage.myObject->GetComponent<Transform>().scale.y),
				0));

			model = glm::rotate(model, glm::radians(renderImage.myObject->GetComponent<Transform>().rotation.z) , glm::vec3(0,0,1));
		}

		glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind the vbo to GL_ARRAY_BUFFER
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);


		glUseProgram(shaderProgram);
		glBindVertexArray(vao);

		//Set the position in shader program
		GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

		//Set the color in shader program
		GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
		glEnableVertexAttribArray(colAttrib);
		glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));

		//Set the texture coordinate in shader program
		GLint texAttrib = glGetAttribLocation(shaderProgram, "texCoord");
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));


		GLint uniModel = glGetUniformLocation(shaderProgram, "model");
		glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

		GLint uniView = glGetUniformLocation(shaderProgram, "view");
		glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

		GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
		glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}



	//________________________________________________________________________________________
	//vector with a pair refering to the Object and is layer

	std::vector<std::pair<Text, int> > textLayerVector;

	//put in orderedObjects all objects that have an image to render
	for (int i = 0; i < objectsToRender.size(); i++)
	{
		if (objectsToRender[i]->HasComponent<Text>())
		{
			std::vector<Text*> objectText;
			objectText = objectsToRender[i]->GetComponents<Text>();

			for (int i = 0; i < objectText.size(); i++)
			{
				Text text = *objectText[i];
				if (text.isVisible && text.text != "")
				{
					//if the object has an image then it is add to the layer vector

					std::pair<Text, int> objWithTexture;
					objWithTexture.first = text;
					objWithTexture.second = text.layer;

					textLayerVector.push_back(objWithTexture);
				}
			}
		}
	}

	//Sorting the layerVector by the layers
	std::sort(textLayerVector.begin(), textLayerVector.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	for (std::pair<Text, int> pair : textLayerVector)
	{
		Text textToRender = pair.first;

		glUseProgram(textShaderProgram);
		//glUniform3f(glGetUniformLocation(shaderProgram, "color"), 1.0, 1.0, 1.0);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao);

		std::string text = textToRender.text;



		float x = 0.0f;
		float y = 0.0f;
		float scale = 0.01f;

		if (textToRender.myObject->GetComponent<Transform>().parent != nullptr)
		{
			x = textToRender.myObject->GetComponent<Transform>().parent->position.x +
			textToRender.myObject->GetComponent<Transform>().position.x + 
			textToRender.xOffSet;

			y = textToRender.myObject->GetComponent<Transform>().parent->position.y +
				textToRender.myObject->GetComponent<Transform>().position.y +
				textToRender.yOffSet;

			scale = textToRender.size;
		}
		else
		{
			x = textToRender.myObject->GetComponent<Transform>().position.x +
				textToRender.xOffSet;

			y = textToRender.myObject->GetComponent<Transform>().position.y +
				textToRender.yOffSet;

			scale = textToRender.size;
		}

		// iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];
			float xpos = x + ch.Bearing.x * scale;
			float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

			float w = ch.Size.x * scale;
			float h = ch.Size.y * scale;
			// update VBO for each character
			float vertices[] = {
				 xpos,     ypos + h,	1.0,1.0,1.0,	0.0,0.0,	//0
				 xpos,     ypos,       	1.0,1.0,1.0,	0.0,1.0,	//1
				 xpos + w, ypos,       	1.0,1.0,1.0,	1.0,1.0,	//2
				 xpos + w, ypos + h,   	1.0,1.0,1.0,	1.0,0.0		//3
			};


			unsigned int indices[] = { // note that we start from 0!
			0, 1, 3, // first triangle
			1, 2, 3 // second triangle
			};


			glm::mat4 model(1.0f);

			glm::mat4 view(1.0f);

			view = glm::translate(view, glm::vec3(0.f, 0.f, -1.f));

			//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 1.0f, 10.0f);

			float fWindowWidth = windowWidth;
			float fWindowHeight = windowHeight;
			glm::mat4 proj = glm::ortho(0.0f, fWindowWidth, 0.0f, fWindowHeight, 0.0f, 100.0f);

			glBindTexture(GL_TEXTURE_2D, ch.TextureID);

			// update content of VBO memory
			glBindBuffer(GL_ARRAY_BUFFER, vbo); //bind the vbo to GL_ARRAY_BUFFER
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);


			//Set the position in shader program
			GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

			//Set the color in shader program
			GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
			glEnableVertexAttribArray(colAttrib);
			glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));

			//Set the texture coordinate in shader program
			GLint texAttrib = glGetAttribLocation(shaderProgram, "texCoord");
			glEnableVertexAttribArray(texAttrib);
			glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));


			GLint uniModel = glGetUniformLocation(shaderProgram, "model");
			glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

			GLint uniView = glGetUniformLocation(shaderProgram, "view");
			glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

			GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
			glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

			// render glyph texture over quad

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64)
		}
	}

	//_______________________________________________________________________________________-----

	glBindTexture(GL_TEXTURE_2D, 0);

	layerVector.clear();
	SDL_GL_SwapWindow(window);     //Update window (Double buffer)


}


//load texture
void RenderManager::LoadTexture(std::string filePath)
{
	if (!hasTextureCreated[filePath])
	{
		hasTextureCreated[filePath] = true;

		//Create the texture
		GLuint texture;
		glGenTextures(1, &texture);
		glActiveTexture(GL_TEXTURE0 + texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glGenerateMipmap(GL_TEXTURE_2D);
		// set the texture wrapping/filtering options (on the currently bound texture object)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		//loading the texture
		int width, height, nrChannels;

		char* file = &filePath[0];

		unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);



		textureHeight[filePath] = height;
		textureWidth[filePath] = width;

		textureMap[filePath] = texture;
		textureID[filePath] = texture;
		//++textureIDCounter;
	}
}

void RenderManager::GetImageSize(Image* img)
{	 
	std::string filePath = img->filePath;
	//loading the texture
	int width, height, nrChannels;

	char* file = &filePath[0];

	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	img->imageWidth = width;
	img->imageHeight = height;
}

