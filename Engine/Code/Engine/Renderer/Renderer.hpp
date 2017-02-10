#pragma once
#include "Engine/Core/Rgba.hpp"
#include "Engine/Math/AABB2.hpp"
#include "Engine/Math/AABB3.hpp"
#include "Engine/Math/Disc2.hpp"
#include "Engine/Math/Vector3.hpp"
#include "Engine/Math/Vertex3.hpp"
#include "Engine/Renderer/Texture.hpp"
#include "Engine/Renderer/BitmapFont.hpp"
#include <string>
#include <vector>
#include <map>

typedef double GLdouble;
typedef int GLint;

struct Vertex3D_PC {
	Vector3 pos;
	Rgba color;
};

struct Vertex2D_PC {
	Vector2 pos;
	Rgba color;
};

extern const unsigned int PRIMITIVE_QUADS;
extern const unsigned int PRIMITIVE_LINES;
extern const unsigned int PRIMITIVE_POLYGON;

class Renderer {

public:
	Renderer();
	~Renderer();
	void SetOrtho(AABB2 worldBox);
	void SetPerspective(float fovYDegrees, float aspectRatio, float zNear, float zFar);
	void clearToBlack();
	void ClearScreen(const Rgba& bgColor);
	void EnableSmoothLines();
	void PushDrawFrame();
	void TranslateDrawFrame2D(const Vector2& translation, float zTranslate);
	void TranslateDrawFrame3D(const Vector3& translation) const;
	void RotateDrawFrame2D(float degrees, Vector2 rotateOrigin, float zOrigin);
	void RotateDrawFrame3D(float degrees, const Vector3& rotationAxis);
	void ScaleDrawFrame(float xScale, float yScale, float zScale);
	void DrawLine(float startx, float starty, float endx, float endy, Rgba color);
	void DrawLine(const Vector2& start, const Vector2& end, const Rgba& color);
	void DrawLine(const Vector3& start, const Vector3& end, const Rgba& color);
	void PopDrawFrame();
	void SetLineWidth(float size);
	void DrawDot(const Vector2& pos, float size);
	void DrawAABB2(const AABB2& box, const Rgba& color);
	void DrawAABB3Outline(const AABB3& box, const Rgba& color);
	void DrawDisc(const Disc2& disc, const Rgba& color, int numSides);
	void DrawTexturedAABB2(const AABB2& bounds, const Texture& texture, const Vector2& texCoordsAtMins,const Vector2& textCoordAtMaxs, const Rgba& tint);
	void DrawTexturedAABB2(const AABB2& bounds, const Texture& texture, const AABB2& texCoords, const Rgba& tint);

	void DrawVertexArray2D(const Vertex2D_PC *vertexArry, int numVerts, unsigned int primitiveDrawMove);

	void DrawTexturedQuad3(const Texture& texture, const Vertex3& vert0, const Vertex3& vert1, const Vertex3& vert2, const Vertex3& vert3);
	void DrawTexturedQuad3(const Texture& texture, const std::vector<Vertex3> vertArray);
	void DrawVertexArray3D(const Texture& texture, const std::vector<Vertex3> vertArray, unsigned int primitiveDrawMode);
	void DrawVertexArray3D(const Vertex3* verts, int numVerts, unsigned int primitiveDrawMode);

	Texture*  CreateOrGetTexture(const std::string& imageFilePath);
	BitmapFont* CreateOrGetFont(const std::string& bitmapFontName);
	void SetBlendModeToAlpha();
	void SetBlendModeToAdd();

	void BindTexture(const Texture* texture);

	//VBO stuff
	void DrawVBO3D_PCT(unsigned int vboID, int numVertexes, unsigned int primitiveDrawMode);
	unsigned int CreateVBO();
	void DestroyVBO(unsigned int vboID);
	void UpdateVBO(unsigned int vboID, Vertex3* vertexArray, int numVertexes);
	

private:
	Texture* CreateTextureFromFile(const std::string& imageFilePath);
	unsigned int CreateOpenGLTexture(unsigned char* imageTexelBytes, int width, int height, int bytesPerTexel);
	Texture* GetTexture(const std::string& imageFilePath);


    
    std::vector<Texture*> m_alreadyLoadedTextures;
	//std::map<std::string, BitmapFont*> m_alreadyLoadedFonts;
	
public:
    void renderSolidSphere(GLdouble radius, GLint slices, GLint stacks);
    void renderWireSphere(GLdouble radius, GLint slices, GLint stacks);
    void renderAxis(float lenght);
};