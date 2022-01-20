#pragma once
#include "core.h"
#include "delta_time.h"

#include "layer.h"

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