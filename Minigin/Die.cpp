#include "MiniginPCH.h"
#include "Die.h"

#include "Qbert.h"

void Die::execute(dae::GameObject& gameObject)
{
	dae::Qbert* qbert = dynamic_cast<dae::Qbert*>(&gameObject);
	qbert->Die();
}
