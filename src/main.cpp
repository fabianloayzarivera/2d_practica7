#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION


#include <glfw3.h>
#include <stb_image.h>
#include <Vec2.h>
#include <list>
#include <world.h>
using namespace std;

ltex_t *createTexture(const char *filename, int *width, int *height);
void beeUpdatePosAngle(float &angle,  double &xposBee, double &yposBee, Vec2 mousePos, Vec2 &beePos, float deltaTime);
inline std::string extractPath(const std::string& filename);

int main() {

	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);
	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}
	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);
	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);
	int screenWidth, screenHeight;
	Vec2 screenSize(800, 600);

	World world;
	int widthSprite		= 192;
	int heightSprite		= 32;
	Sprite IdlePlayerSprite	= Sprite(createTexture("./data/idle.png", &widthSprite, &heightSprite), 1, 1);
	
	IdlePlayerSprite.setPosition(Vec2(0, 0));
	IdlePlayerSprite.setBlend(BLEND_ALPHA);
	IdlePlayerSprite.setFps(8);
	IdlePlayerSprite.setPivot(Vec2(0.5f, 0.5f));	
		

	int widthBack = 128;
	int heightBack = 128;
	world.setBackground(0, createTexture("./data/background.png", &widthBack, &heightBack));
	world.setScrollRatio(0, 0.4);
	world.setScrollSpeed(0, Vec2(0, 0));

	string tilesPath = extractPath("./data/map.tmx");
	tilesPath += "tiles.png";

	int widthTiles = 256;
	int heightTiles = 160;

	world.setMapTiles(createTexture(tilesPath.c_str(), &widthTiles, &heightTiles));
	world.loadMap("./data/map.tmx", 0);

	
	world.addSprite(IdlePlayerSprite);

	int beeFrame;
	float frame = 0;
	double lastTime = glfwGetTime();
	double xposMouse = 0;
	double yposMouse = 0;
	double xposBee = 0;
	double yposBee = 0;
	Vec2 mousePos;
	float angle=0;
	Vec2 cameraPosition = world.getCameraPosition();
	world.updateWorldSize();
	Vec2 beePos;
	
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);
		screenSize = Vec2(screenWidth, screenHeight);
		world.setScreenSize(screenSize);
		lgfx_clearcolorbuffer(world.getClearRed(), world.getClearGreen(), world.getClearBlue());
		lgfx_setorigin(world.getCameraPosition().x, world.getCameraPosition().y);

		glfwGetCursorPos(window, &xposMouse, &yposMouse);
		mousePos = Vec2(static_cast<float>(xposMouse), static_cast<float>(yposMouse));
		mousePos.x += world.getCameraPosition().x;
		mousePos.y += world.getCameraPosition().y;
		beeUpdatePosAngle(angle, xposBee, yposBee, mousePos, beePos, deltaTime);

		world.updateSpritePosition(beePos);
		world.updateSpriteAngle(angle);		
		world.update(deltaTime);
		world.draw(screenSize);
		world.updateCameraPosition(beePos, deltaTime);
		
		
		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();


	}

	return 0;
}

ltex_t* createTexture(const char *filename, int *width, int *height) {

	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	if (buffer != NULL) {
	}
	else {
		cout << "buffer empty";
	}

	ltex_t* tex = ltex_alloc(*width, *height, 0);

	ltex_setpixels(tex, buffer);

	stbi_image_free(buffer);

	return tex;
	//ltex_free(ltex_t* tex);

}

void beeUpdatePosAngle(float &angle, double &xposBee, double &yposBee, Vec2 mousePos, Vec2 &beePos, float deltaTime) {
	Vec2 dist;
	Vec2 direction;
	float pointsX;
	float pointsY;
	dist = mousePos - beePos;
	direction = dist.norm();

	if (dist.lenght() > 2) {
		pointsX = 128.0f * deltaTime * direction.x;
		pointsY = 128.0f * deltaTime * direction.y;
		if (xposBee < mousePos.x && angle > -15) {
			angle -= (32 * deltaTime);
		}
		else if (angle < 15) {
			angle += (32 * deltaTime);
		}
	}
	else {
		pointsX = 0;
		pointsY = 0;
		if (angle < 0) {
			angle += (32 * deltaTime);
		}
		else if (angle > 0) {
			angle -= (32 * deltaTime);
		}
	}
	xposBee += pointsX;
	yposBee += pointsY;

	beePos = Vec2(xposBee, yposBee);
}

inline std::string extractPath(const std::string& filename) {
	std::string filenameCopy = filename;
	while (filenameCopy.find("\\") != std::string::npos) {
		filenameCopy.replace(filenameCopy.find("\\"), 1, "/");
	}
	filenameCopy = filenameCopy.substr(0, filenameCopy.rfind('/'));
	if (filenameCopy.size() > 0) filenameCopy += "/";
	return filenameCopy;
}
