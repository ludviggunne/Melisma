#include "melisma/layer/layer_stack.h"

#include "melisma/core.h"

namespace melisma {


	LayerStack::LayerStack()
	{
	}

	void LayerStack::PushLayerTop(Ref<Layer> layer)
	{
		m_Layers.insert(m_Layers.begin(), layer);
		layer->OnAttach();
	}

	void LayerStack::PushLayerBottom(Ref<Layer> layer)
	{
		m_Layers.push_back(layer);
		layer->OnAttach();
	}

	Ref<Layer> LayerStack::PopLayer(Ref<Layer> layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);

		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			layer->OnDetach();
		}

		return layer;
	}

	bool LayerStack::OnEvent(Event &e)
	{
		for (auto layer : m_Layers) {
			if (layer->OnEvent(e))
				return true;
		}

		return false;
	}

	void LayerStack::OnUpdate(const DeltaTime &deltaTime)
	{
		// Updates from top down
		for (auto layer : m_Layers) layer->OnUpdate(deltaTime);
	}

	void LayerStack::OnRender() const
	{
		// Renders from bottom up
		for (auto layer_it = m_Layers.rbegin(); layer_it != m_Layers.rend(); ++layer_it) {
			(*layer_it)->OnRender();
		}
	}

}