#pragma once

#include "Component.h"
#include "Transform.h"
#include "Object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>



struct TransformComponent : public ComponentImpl<TransformComponent>
{
public:
	// Local
	Transform& transform()
	{
		return m_transform;
	}

	const Transform& GetTransform() const
	{
		return m_transform;
	}

	glm::mat4 GetLocalMatrix() const
	{
		const glm::mat4 t = glm::translate(glm::mat4(1.0f), m_transform.m_position);
		const glm::mat4 r = glm::mat4_cast(m_transform.m_rotation);
		const glm::mat4 s = glm::scale(glm::mat4(1.0f), m_transform.m_scale);

		return t * r * s;
	}

	glm::vec3& localPosition()
	{
		return m_transform.m_position;
	}

	const glm::vec3& GetLocalPosition() const
	{
		return m_transform.m_position;
	}

	glm::quat& localRotation()
	{
		return m_transform.m_rotation;
	}

	const glm::quat& GetLocalRotation() const
	{
		return m_transform.m_rotation;
	}

	glm::vec3& localScale()
	{
		return m_transform.m_scale;
	}

	const glm::vec3& GetLocalScale() const
	{
		return m_transform.m_scale;
	}

	// World
	glm::mat4 GetWorldMatrix(const Object& owner) const
	{
		if (Object* parent = owner.GetParent())
		{
			if (auto* parentTransform = parent->GetComponent<TransformComponent>())
				return parentTransform->GetWorldMatrix(*parent) * GetLocalMatrix();
		}

		return GetLocalMatrix();
	}

	Transform GetWorldTransform(const Object& owner) const
	{
		glm::mat4 worldMatrix = GetWorldMatrix(owner);

		Transform worldTransform;

		glm::vec3 skew;
		glm::vec4 perspective;

		glm::decompose(worldMatrix, worldTransform.m_scale, worldTransform.m_rotation, worldTransform.m_position, skew, perspective);

		// decompose returns the conjugate quaternion; invert it back
		worldTransform.m_rotation = glm::conjugate(worldTransform.m_rotation);

		return worldTransform;
	}

	glm::vec3 GetWorldPosition(const Object& owner) const
	{
		return GetWorldTransform(owner).m_position;
	}

	glm::quat GetWorldRotation(const Object& owner) const
	{
		return GetWorldTransform(owner).m_rotation;
	}

	glm::vec3 GetWorldScale(const Object& owner) const
	{
		return GetWorldTransform(owner).m_scale;
	}

	void SetWorldPosition(const Object& owner, const glm::vec3& position)
	{
		if (Object* parent = owner.GetParent())
		{
			if (auto* parentTransform = parent->GetComponent<TransformComponent>())
			{
				const glm::mat4 parentWorldMatrix = parentTransform->GetWorldMatrix(*parent);

				m_transform.m_position = glm::vec3(glm::inverse(parentWorldMatrix) * glm::vec4(position, 1.0f));

				return;
			}
		}

		m_transform.m_position = position;
	}

	void SetWorldRotation(const Object& owner, const glm::quat& rotation)
	{
		if (Object* parent = owner.GetParent())
		{
			if (auto* parentTransform = parent->GetComponent<TransformComponent>())
			{
				const glm::quat parentWorldRotation = parentTransform->GetWorldTransform(*parent).m_rotation;

				m_transform.m_rotation = glm::inverse(parentWorldRotation) * rotation;

				return;
			}
		}

		m_transform.m_rotation = rotation;
	}

	void SetWorldScale(const Object& owner, const glm::vec3& scale)
	{
		if (Object* parent = owner.GetParent())
		{
			if (auto* parentTransform = parent->GetComponent<TransformComponent>())
			{
				const glm::vec3 parentWorldScale = parentTransform->GetWorldTransform(*parent).m_scale;

				m_transform.m_scale = scale / parentWorldScale;

				return;
			}
		}

		m_transform.m_scale = scale;
	}

private:
	Transform m_transform;
};
