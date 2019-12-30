#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/matrix_access.hpp>
class math_manager
{
public:
	static glm::mat4 CreateTRSMatrix(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		glm::mat4 matrix = glm::identity<glm::mat4>();
		matrix = glm::scale(matrix, scale);
		matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		matrix = glm::translate(matrix, position);
		return matrix;
	}

};