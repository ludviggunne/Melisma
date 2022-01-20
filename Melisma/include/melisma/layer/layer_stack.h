#pragma once
#include "melisma/core.h"
#include "melisma/delta_time.h"
#include "melisma/event/event.h"
#include "layer.h"
#include "melisma/pointers.h"

#include <vector>

namespace melisma {

	class melismaAPI LayerStack {
	public:
		LayerStack();

		void PushLayerTop(Ref<Layer>);
		void PushLayerBottom(Ref<Layer>);

		Ref<Layer> PopLayer(Ref<Layer>);

		bool OnEvent(Event &);
		void OnUpdate(const DeltaTime &deltaTime);

	private:
		std::vector<Ref<Layer>> m_Layers;
	};
}