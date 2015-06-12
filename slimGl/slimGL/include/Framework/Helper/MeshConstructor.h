#pragma once

#include <Framework/Drawable/Model.t>
#include <Framework/VertexData/Vertex3DTexNorm.h>
#include <Framework/Helper/VecHelper.h>

/*!
*	\brief a static class which constructs meshes
*/
class MeshConstructor
{
public:
	/*!
	*	\brief		constructing a mesh out of a box
	*	\param box	the box you want to construct the mesh from
	*	\return		the mesh for the bounding box
	*/
	static std::shared_ptr<Mesh<Vertex3DNormTex>> constructBoundingBoxMesh(const Box &box);

	/*!
	*	\brief			construct a convex polygon out of vertices
	*	\param vertices	the vertices you want to construct the convex polygon mesh from
	*	\param axis1	the first axis of the projection plane
	*	\param axis2	the second axis of the projection plane
	*	\param rotation	the transformation matrix, which should be applied to the vertices
	*	\param accuracy	the precision of the coordinates (default is 1000)
	*	\return			the mesh of th projected polygon
	*/
	static std::shared_ptr<Mesh<Vertex3DNormTex>> constructConvexPolygonMesh(const std::vector<Vertex3DNormTex> &vertices, const glm::vec3 &axis1, const glm::vec3 &axis2, const glm::vec3 rotation = glm::vec3(0), float accuracy = 1000.0f);

};