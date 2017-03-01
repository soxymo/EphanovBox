#include "Renderer.hpp"

//Open GL stuff 
#pragma comment( lib, "opengl32" ) // Link in the OpenGL32.lib static library
#pragma comment( lib, "Glu32" )
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <gl/GL.h>
#include "ThirdParty/stb/stb_image.h"
#include "Engine/Core/ErrorWarningAssert.hpp"
#include "Engine/Core/StringUtils.hpp"
#include <gl/GLU.h>
#include "ThirdParty/OpenGL/glext.h"
#include "ThirdParty/OpenGL/wglext.h"

const unsigned int PRIMITIVE_QUADS = GL_QUADS;
const unsigned int PRIMITIVE_LINES = GL_LINES;
const unsigned int PRIMITIVE_POLYGON = GL_POLYGON;

const float m_PI = 3.1415926535897932384626f;


PFNGLGENBUFFERSPROC		glGenBuffers = nullptr;
PFNGLBINDBUFFERPROC		glBindBuffer = nullptr;
PFNGLBUFFERDATAPROC		glBufferData = nullptr;
PFNGLDELETEBUFFERSPROC  glDeleteBuffers = nullptr;


Renderer::Renderer() {

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");

	GUARANTEE_OR_DIE(glGenBuffers != nullptr, "ERROR: This video card does not support glGenBuffers!");
	GUARANTEE_OR_DIE(glDeleteBuffers != nullptr, "ERROR: This video card does not support glGenBuffers!");
	GUARANTEE_OR_DIE(glBindBuffer != nullptr, "ERROR: This video card does not support glGenBuffers!");
	GUARANTEE_OR_DIE(glBufferData != nullptr, "ERROR: This video card does not support glGenBuffers!");


	//move smooth lines here!!!
}

Renderer::~Renderer() {
	for (unsigned int i = 0; i < m_alreadyLoadedTextures.size(); i++)
		delete m_alreadyLoadedTextures[i];
	m_alreadyLoadedTextures.clear();
}

void Renderer::SetOrtho(AABB2 worldBox) {
	glLoadIdentity();
	glOrtho(worldBox.min.x,worldBox.max.x, worldBox.min.y, worldBox.max.y, 0.f, 1.f);
}

void Renderer::SetPerspective(float fovYDegrees, float aspectRatio, float zNear, float zFar) {

	glLoadIdentity();
	gluPerspective(fovYDegrees, aspectRatio, zNear, zFar);


	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(1.f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	//look into glColor4ub();
}

void Renderer::clearToBlack() {
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::ClearScreen(const Rgba& bgColor) {
	float r, g, b, a;
	bgColor.GetAsFloats(r, g, b, a);
	glClearColor(r,g,b,a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::EnableSmoothLines()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glLineWidth(2.f);
	glEnable(GL_LINE_SMOOTH);
}

void Renderer::PushDrawFrame() {
	glPushMatrix();
}

void Renderer::TranslateDrawFrame2D(const Vector2& translation, float zTranslate) {
	glTranslatef(translation.x, translation.y, zTranslate);
}

void Renderer::TranslateDrawFrame3D(const Vector3& translation) const {
	glTranslatef(translation.x, translation.y, translation.z);
}

void Renderer::RotateDrawFrame2D(float degrees, Vector2 rotateOrigin, float zOrigin) {
	glRotatef(degrees, rotateOrigin.x, rotateOrigin.y, zOrigin);
}

void Renderer::RotateDrawFrame3D(float degrees, const Vector3& rotationAxis) {
	glRotatef(degrees, rotationAxis.x, rotationAxis.y, rotationAxis.z);
}

void Renderer::ScaleDrawFrame(float xScale, float yScale, float zScale) {
	glScalef(xScale, yScale, zScale);
}



void Renderer::DrawLine(float startx, float starty, float endx, float endy, Rgba color) {
	BindTexture(CreateOrGetTexture("Data/Images/White.png"));

	Vertex3 lineVerts[2] = { Vertex3(Vector3(startx, starty, 0), Vector2(0,0), color), Vertex3(Vector3(endx, endy, 0), Vector2(0,0), color) };
	DrawVertexArray3D(&lineVerts[0], 2, PRIMITIVE_LINES);
}





void Renderer::DrawLine(const Vector3& start, const Vector3& end, const Rgba& color) {
	BindTexture(CreateOrGetTexture("Data/Images/White.png"));

	Vertex3 lineVerts[2] = { Vertex3(start, Vector2(0,0), color), Vertex3(end, Vector2(0,0), color) };
	DrawVertexArray3D(&lineVerts[0], 2, PRIMITIVE_LINES);
}

void Renderer::DrawLine(const Vector2& start, const Vector2& end, const Rgba& color) {
	BindTexture(CreateOrGetTexture("Data/Images/White.png"));

	Vertex3 lineVerts[2] = { Vertex3(Vector3(start.x, start.y, 0), Vector2(0,0), color), Vertex3(Vector3(end.x, end.y, 0), Vector2(0,0), color) };
	DrawVertexArray3D(&lineVerts[0], 2, PRIMITIVE_LINES);
}



void Renderer::PopDrawFrame() {
	glPopMatrix();
}

void Renderer::SetLineWidth(float size) {
	glLineWidth(size);
}

void Renderer::DrawDot(const Vector2& pos, float size) {
	//glLineWidth(size);
	size;
	DrawLine(pos, pos + Vector2(.5f, 0), Rgba());
	//glLineWidth(2.f);
	
}

void Renderer::DrawAABB2(const AABB2& box, const Rgba& color) {
	BindTexture(CreateOrGetTexture("Data/Images/White.png"));

	Vertex3 vertArray[4];
	vertArray[0]=Vertex3(Vector3(box.min.x, box.min.y, 0), Vector2(0,0), color);
	vertArray[1]=	Vertex3(Vector3(box.max.x, box.min.y, 0), Vector2(0, 0), color);
	vertArray[2]=	Vertex3(Vector3(box.max.x, box.max.y, 0), Vector2(0, 0), color);
	vertArray[3]=	Vertex3(Vector3(box.min.x, box.max.y, 0), Vector2(0, 0), color);
	//vertArray[0]=	//Vertex3(Vector3(box.min.x, box.min.y, 0, Vector2(0, 0), color);
	DrawVertexArray3D(&vertArray[0], 4, GL_QUADS);

	
// 	const int NUM_VERTS = 2;
// 	Vertex3D_PC vertexes[NUM_VERTS];
// 	vertexes[0].pos = start;
// 	vertexes[0].color = color;
// 	vertexes[1].pos = end;
// 	vertexes[1].color = color;
// 
// 	glEnableClientState(GL_VERTEX_ARRAY);
// 	glEnableClientState(GL_COLOR_ARRAY);
// 	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
// 
// 	glVertexPointer(3, GL_FLOAT, sizeof(Vertex3D_PC), &vertexes[0].pos);
// 	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3D_PC), &vertexes[0].color); // float RGBAs
// 																				  // 	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3D_PCT), &m_vertexes[0].m_texCoords);
// 
// 	glDrawArrays(GL_LINES, 0, NUM_VERTS);
// 
// 	glDisableClientState(GL_VERTEX_ARRAY);
// 	glDisableClientState(GL_COLOR_ARRAY);
}

void Renderer::DrawAABB3Outline(const AABB3& box, const Rgba& color) { //TODO - add more faces here.
	DrawLine(box.min, Vector3(box.max.x,box.min.y, box.min.z), color);
	DrawLine(box.min, Vector3(box.min.x, box.max.y, box.min.z), color);
	DrawLine(box.min, Vector3(box.min.x, box.min.y, box.max.z), color);

	DrawLine(Vector3(box.min.x, box.min.y, box.max.z), Vector3(box.max.x, box.min.y, box.max.z), color);
	DrawLine(Vector3(box.min.x, box.min.y, box.max.z), Vector3(box.min.x, box.max.y, box.max.z), color);

	DrawLine(box.max, Vector3(box.min.x, box.max.y, box.max.z), color);
	DrawLine(box.max, Vector3(box.max.x, box.min.y, box.max.z), color);
	DrawLine(box.max, Vector3(box.max.x, box.max.y, box.min.z), color);

	DrawLine(Vector3(box.max.x, box.max.y, box.min.z), Vector3(box.min.x, box.max.y, box.min.z), color);
	DrawLine(Vector3(box.max.x, box.max.y, box.min.z), Vector3(box.max.x, box.min.y, box.min.z), color);

	DrawLine(Vector3(box.max.x, box.min.y, box.min.z), Vector3(box.max.x, box.min.y, box.max.z), color);
	DrawLine(Vector3(box.min.x, box.max.y, box.min.z), Vector3(box.min.x, box.max.y, box.max.z), color);
}

void Renderer::DrawDisc(const Disc2& disc, const Rgba& color, int numSides) {
	Vector2 drawVector(disc.radius, 0);
	const float degreeChange = 360.f / numSides;
	for (int lineCount = 0; lineCount < numSides; lineCount++) {
		Vector2 preSpin(drawVector);
		drawVector.RotateDegrees(degreeChange);
		DrawLine(disc.center + preSpin, disc.center + drawVector, color);
	}
}

void Renderer::DrawTexturedAABB2(const AABB2& bounds, const Texture& texture, const Vector2& texCoordsAtMins, const Vector2& texCoordsAtMaxs, const Rgba& tint) {
	BindTexture(&texture);

	Vertex3 vertArray[4];
	vertArray[0] = Vertex3(Vector3(bounds.min.x, bounds.min.y, 0), Vector2(texCoordsAtMins.x, texCoordsAtMins.y), tint);
	vertArray[1] = Vertex3(Vector3(bounds.max.x, bounds.min.y, 0), Vector2(texCoordsAtMaxs.x, texCoordsAtMins.y), tint);
	vertArray[2] = Vertex3(Vector3(bounds.max.x, bounds.max.y, 0), Vector2(texCoordsAtMaxs.x, texCoordsAtMaxs.y), tint);
	vertArray[3] = Vertex3(Vector3(bounds.min.x, bounds.max.y, 0), Vector2(texCoordsAtMins.x, texCoordsAtMaxs.y), tint);
	//vertArray[0]=	//Vertex3(Vector3(box.min.x, box.min.y, 0, Vector2(0, 0), color);
	DrawVertexArray3D(&vertArray[0], 4, GL_QUADS);
}

void Renderer::DrawTexturedAABB2(const AABB2& bounds, const Texture& texture, const AABB2& texCoords, const Rgba& tint) {
	DrawTexturedAABB2(bounds, texture, texCoords.min, texCoords.max, tint);
}



void Renderer::DrawTexturedQuad3(const Texture& texture, const Vertex3& vert0, const Vertex3& vert1, const Vertex3& vert2, const Vertex3& vert3) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.m_textureID);

	const int NUM_VERTS = 4;

	Vertex3 vertArray[4];
	vertArray[0] = vert0;
	vertArray[1] = vert1;
	vertArray[2] = vert2;
	vertArray[3] = vert3;
	


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex3), &vertArray[0].m_pos);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3), &vertArray[0].m_tint); // float RGBAs
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3), &vertArray[0].m_texCoords);

	glDrawArrays(GL_QUADS, 0, NUM_VERTS);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Renderer::DrawTexturedQuad3(const Texture& texture, const std::vector<Vertex3> vertArray) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.m_textureID);

	const int NUM_VERTS = vertArray.size();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex3), &vertArray[0].m_pos);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3), &vertArray[0].m_tint); // float RGBAs
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3), &vertArray[0].m_texCoords);

	glDrawArrays(GL_QUADS, 0, NUM_VERTS);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}



void Renderer::DrawVertexArray3D(const Texture& texture, const std::vector<Vertex3> vertArray, unsigned int primitiveDrawMode) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture.m_textureID);

	const int NUM_VERTS = vertArray.size();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex3), &vertArray[0].m_pos);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3), &vertArray[0].m_tint); // float RGBAs
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3), &vertArray[0].m_texCoords);

	glDrawArrays(primitiveDrawMode, 0, NUM_VERTS);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Renderer::DrawVertexArray3D(const Vertex3* verts, int numVerts, unsigned int primitiveDrawMode) {

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex3), &verts[0].m_pos);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3), &verts[0].m_tint); // float RGBAs
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3), &verts[0].m_texCoords);

	glDrawArrays(primitiveDrawMode, 0, numVerts);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

Texture* Renderer::CreateOrGetTexture(const std::string& imageFilePath) {
	Texture* texture = GetTexture(imageFilePath);
	if (texture)
		return texture;

	texture = CreateTextureFromFile(imageFilePath);
	return texture;
}

// BitmapFont* Renderer::CreateOrGetFont(const std::string& bitmapFontName) {
// 	return new BitmapFont();
// }

void Renderer::SetBlendModeToAlpha() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::SetBlendModeToAdd() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}


void Renderer::BindTexture(const Texture* texture) {
	if (texture) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
	}
	else {
		// #TODO bind default tiny white texture

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, CreateOrGetTexture("Data/Images/White.png")->m_textureID);
	}
}

void Renderer::DrawVBO3D_PCT(unsigned int vboID, int numVertexes, unsigned int primitiveDrawMode) {
	//glBindBuffer(GL_ARRAY_BUFFER, vboID);

	//glPushMatrix();
	//glTranslatef(m_worldMins.x, m_worldMins.y, m_worldMins.z);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex3), (const GLvoid*)offsetof(Vertex3, m_pos));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex3), (const GLvoid*)offsetof(Vertex3, m_tint));
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex3), (const GLvoid*)offsetof(Vertex3, m_texCoords));

	glDrawArrays(primitiveDrawMode, 0, numVertexes);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glPopMatrix();




	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int Renderer::CreateVBO() {
	unsigned int vboID;
	glGenBuffers(1, &vboID);
	return vboID;
}

void Renderer::DestroyVBO(unsigned int vboID) {
	glDeleteBuffers(1, &vboID);
}

void Renderer::UpdateVBO(unsigned int vboID, Vertex3* vertexArray, int numVertexes) {
	size_t vertexArrayNumBytes = sizeof(Vertex3) * numVertexes;
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, vertexArrayNumBytes, &vertexArray[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}



Texture* Renderer::CreateTextureFromFile(const std::string& imageFilePath) {
	// Load image data
	int width = 0;
	int height = 0;
	int bytesPerTexel = 0;
	unsigned char* imageTexelBytes = stbi_load(imageFilePath.c_str(), &width, &height, &bytesPerTexel, 0);
	GUARANTEE_OR_DIE(imageTexelBytes != nullptr, Stringf("Failed to load image file \"%s\" - file not found!", imageFilePath.c_str()));
	GUARANTEE_OR_DIE(bytesPerTexel == 3 || bytesPerTexel == 4, Stringf("Failed to load image file \"%s\" - image had unsupported %i bytes per texel (must be 3 or 4)", imageFilePath.c_str(), bytesPerTexel));

	// Create texture on video card, and send image (texel) data
	unsigned int openGLTextureID = CreateOpenGLTexture(imageTexelBytes, width, height, bytesPerTexel);
	stbi_image_free(imageTexelBytes);

	// Create (new) a Texture object
	Texture* texture = new Texture();
	texture->m_textureID = openGLTextureID;
	texture->m_imageFilePath = imageFilePath;
	texture->m_texelDimensions.SetXY(width, height);

	m_alreadyLoadedTextures.push_back(texture);
	return texture;
}

unsigned int Renderer::CreateOpenGLTexture(unsigned char* imageTexelBytes, int width, int height, int bytesPerTexel) {
	// Create a texture ID (or "name" as OpenGL calls it) for this new texture
	unsigned int openGLTextureID = 0xFFFFFFFF;
	glGenTextures(1, &openGLTextureID);

	// Enable texturing
	glEnable(GL_TEXTURE_2D);

	// Tell OpenGL that our pixel data is single-byte aligned
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Tell OpenGL to bind (set) this as the currently active texture
	glBindTexture(GL_TEXTURE_2D, openGLTextureID);

	// Set texture clamp vs. wrap (repeat)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // one of: GL_CLAMP or GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // one of: GL_CLAMP or GL_REPEAT

																  // Set magnification (texel > pixel) and minification (texel < pixel) filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // one of: GL_NEAREST, GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);  // one of: GL_NEAREST, GL_LINEAR, GL_NEAREST_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_LINEAR_MIPMAP_LINEAR

	GLenum bufferFormat = GL_RGBA; // the format our source pixel data is currently in; any of: GL_RGB, GL_RGBA, GL_LUMINANCE, GL_LUMINANCE_ALPHA, ...
	if (bytesPerTexel == 3)
		bufferFormat = GL_RGB;

	GLenum internalFormat = bufferFormat; // the format we want the texture to me on the card; allows us to translate into a different texture format as we upload to OpenGL

	glTexImage2D(			// Upload this pixel data to our new OpenGL texture
		GL_TEXTURE_2D,		// Creating this as a 2d texture
		0,					// Which mipmap level to use as the "root" (0 = the highest-quality, full-res image), if mipmaps are enabled
		internalFormat,		// Type of texel format we want OpenGL to use for this texture internally on the video card
		width,				// Texel-width of image; for maximum compatibility, use 2^N + 2^B, where N is some integer in the range [3,10], and B is the border thickness [0,1]
		height,				// Texel-height of image; for maximum compatibility, use 2^M + 2^B, where M is some integer in the range [3,10], and B is the border thickness [0,1]
		0,					// Border size, in texels (must be 0 or 1)
		bufferFormat,		// Pixel format describing the composition of the pixel data in buffer
		GL_UNSIGNED_BYTE,	// Pixel color components are unsigned bytes (one byte per color/alpha channel)
		imageTexelBytes);	// Location of the actual pixel data bytes/buffer

	return openGLTextureID;
}

Texture* Renderer::GetTexture(const std::string& imageFilePath) {
	for (int textureIndex = 0; textureIndex < (int)m_alreadyLoadedTextures.size(); ++textureIndex)
	{
		Texture* texture = m_alreadyLoadedTextures[textureIndex];
		if (imageFilePath == texture->m_imageFilePath)
			return texture;
	}

	return nullptr;
}

static void circleTable(double **sint, double **cost, const int n)
{
    int i;

    /* Table size, the sign of n flips the circle direction */

    const int size = abs(n);

    /* Determine the angle between samples */

    const double angle = 2 * m_PI / (double)n;

    /* Allocate memory for n samples, plus duplicate of first entry at the end */

    *sint = (double *)calloc(sizeof(double), size + 1);
    *cost = (double *)calloc(sizeof(double), size + 1);

    /* Bail out if memory allocation fails, fgError never returns */

    if (!(*sint) || !(*cost))
    {
        free(*sint);
        free(*cost);
        //fgError("Failed to allocate memory in circleTable");
    }

    /* Compute cos and sin around the circle */

    for (i = 0; i < size; i++)
    {
        (*sint)[i] = sin(angle*i);
        (*cost)[i] = cos(angle*i);
    }

    /* Last sample is duplicate of the first */

    (*sint)[size] = (*sint)[0];
    (*cost)[size] = (*cost)[0];
}

/*
* Draws a solid sphere
*/
void Renderer::renderSolidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    int i, j;

    /* Adjust z and radius as stacks are drawn. */

    double z0, z1;
    double r0, r1;

    /* Pre-computed circle */

    double *sint1, *cost1;
    double *sint2, *cost2;
    circleTable(&sint1, &cost1, -slices);
    circleTable(&sint2, &cost2, stacks * 2);

    /* The top stack is covered with a triangle fan */

    z0 = 1.0;
    z1 = cost2[1];
    r0 = 0.0;
    r1 = sint2[1];

    glBegin(GL_TRIANGLE_FAN);

    glNormal3d(0, 0, 1);
    glVertex3d(0, 0, radius);

    for (j = slices; j >= 0; j--)
    {
        glNormal3d(cost1[j] * r1, sint1[j] * r1, z1);
        glVertex3d(cost1[j] * r1*radius, sint1[j] * r1*radius, z1*radius);
    }

    glEnd();

    /* Cover each stack with a quad strip, except the top and bottom stacks */

    for (i = 1; i<stacks - 1; i++)
    {
        z0 = z1; z1 = cost2[i + 1];
        r0 = r1; r1 = sint2[i + 1];

        glBegin(GL_QUAD_STRIP);

        for (j = 0; j <= slices; j++)
        {
            glNormal3d(cost1[j] * r1, sint1[j] * r1, z1);
            glVertex3d(cost1[j] * r1*radius, sint1[j] * r1*radius, z1*radius);
            glNormal3d(cost1[j] * r0, sint1[j] * r0, z0);
            glVertex3d(cost1[j] * r0*radius, sint1[j] * r0*radius, z0*radius);
        }

        glEnd();
    }

    /* The bottom stack is covered with a triangle fan */

    z0 = z1;
    r0 = r1;

    glBegin(GL_TRIANGLE_FAN);

    glNormal3d(0, 0, -1);
    glVertex3d(0, 0, -radius);

    for (j = 0; j <= slices; j++)
    {
        glNormal3d(cost1[j] * r0, sint1[j] * r0, z0);
        glVertex3d(cost1[j] * r0*radius, sint1[j] * r0*radius, z0*radius);
    }

    glEnd();

    /* Release sin and cos tables */

    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}

/*
* Draws a solid sphere
*/
void Renderer::renderWireSphere(GLdouble radius, GLint slices, GLint stacks, Rgba color)
{
    int i, j;

	float red, g, b, a;
	color.GetAsFloats(red, g, b, a);
    glColor3f(red, g, b);

    /* Adjust z and radius as stacks and slices are drawn. */

    double r;
    double x, y, z;

    /* Pre-computed circle */

    double *sint1, *cost1;
    double *sint2, *cost2;
    circleTable(&sint1, &cost1, -slices);
    circleTable(&sint2, &cost2, stacks * 2);

    /* Draw a line loop for each stack */

    for (i = 1; i<stacks; i++)
    {
        z = cost2[i];
        r = sint2[i];

        glBegin(GL_LINE_LOOP);

        for (j = 0; j <= slices; j++)
        {
            x = cost1[j];
            y = sint1[j];

            glNormal3d(x, y, z);
            glVertex3d(x*r*radius, y*r*radius, z*radius);
        }

        glEnd();
    }

    /* Draw a line loop for each slice */

    for (i = 0; i<slices; i++)
    {
        glBegin(GL_LINE_STRIP);

        for (j = 0; j <= stacks; j++)
        {
            x = cost1[i] * sint2[j];
            y = sint1[i] * sint2[j];
            z = cost2[j];

            glNormal3d(x, y, z);
            glVertex3d(x*radius, y*radius, z*radius);
        }

        glEnd();
    }

    /* Release sin and cos tables */

    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}

void Renderer::renderAxis(float lenght)
{
    //Use Red, Green, Blue for X Y Z respectively
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    //X axis
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(lenght, 0.0f, 0.0f);
    //Y axis
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, lenght, 0.0f);
    //Z axis
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, lenght);
    glEnd();
}