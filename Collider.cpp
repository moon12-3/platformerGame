#include "Collider.hpp"

Collider::Collider(RectangleShape& cBody) :
	body(cBody)
{
}

void Collider::EnemyMove(Collider& other, int* direction) {
	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		if (intersectX > intersectY) {	// Y�� ������ X�� ���� ũ�ٸ�
			if (deltaX > 0.0f) {	// ������ ���� �浹
				//if (intersectY != -GRAVITY)
					*direction = -1;
				
			}
			else {	// �����ʿ��� �浹
				
			}
		}
		else {
			if (deltaY > 0.0f) {
				*direction = -1;
			}
			else {
				*direction = -1;
			}
		}

	}
}

bool Collider::CheckCollision(Collider& other, Vector2f& direction, float push) {
	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();


	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = std::min(std::max(push, 0.0f), 1.0f);

		if (intersectX > intersectY) {	// Y�� ������ X�� ���� ũ�ٸ�
			if (deltaX > 0.0f) {	// ���ʿ��� �浹
				Move(intersectX * (1.0f - push), 0.0f);	// 0�̸� BLOCK�� �ش� �������� �б�
				if(intersectY!=-GRAVITY)
					other.Move(-intersectX * push, 0.0f);	// X�δ� ��� �����̰�, Y�� ����
			}
			else {	// �����ʿ��� �浹
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);
			}
		}
		else {
			if (deltaY > 0.0f) {
				Move(0.0f, intersectY * (1.0f - push));
				other.Move(0.0f , -intersectY * push);
			}
			else {
				Move(0.0f, -intersectY * (1.0f - push));
				other.Move(0.0f, intersectY * push);
			}
		}
		return true;
	}

	return false;
}