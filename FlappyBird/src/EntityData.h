#pragma once

#include "Shape.h"
#include "Texture.h"
#include <memory>
#include "ResourceManager.h"

class EntityData
{
public:
	EntityData(const std::string& texturePath);

	std::shared_ptr<Shape> GetShape() { return m_shape; }
	std::shared_ptr<Texture> GetTexture() const { return m_texture; }
	std::shared_ptr<Texture> m_texture;

	bool operator==(const EntityData& other) const
	{
		if (!this->m_texture->GetTexturePath().empty() && !other.m_texture->GetTexturePath().empty())
			return this->m_texture->GetTexturePath() == other.m_texture->GetTexturePath();
		else
			return false;
	}
private:
	std::shared_ptr<Shape> m_shape;
	
};
