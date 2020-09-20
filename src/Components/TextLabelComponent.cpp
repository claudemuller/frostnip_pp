#include "TextLabelComponent.h"
#include "TransformComponent.h"

TextLabelComponent::TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color colour)
: text(text), fontFamily(fontFamily), colour(colour) {
	position.x = x;
	position.y = y;
	setLabelText(text, fontFamily);
}

void TextLabelComponent::update(float deltaTime) {
	if (owner->hasComponent<TransformComponent>()) {
		TransformComponent* transform = owner->getComponent<TransformComponent>();
		position.x = transform->position.getX();
		position.y = transform->position.getY();
	}
}

void TextLabelComponent::setLabelText(std::string text, std::string fontId) {
	SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->getFont(fontId), text.c_str(), colour);
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
}

void TextLabelComponent::render() {
	FontManager::draw(texture, position);
}
