#include "SlippiTimer.h"
#include "DolphinWX/Frame.h"

#include "SlippiPlayback/SlippiPlayback.h"
extern std::unique_ptr<SlippiPlaybackStatus> g_playback_status;

void slippiTimer::Notify()
{
	int totalSeconds = (int) ((g_playback_status->latestFrame + 123) / 60);
	int totalMinutes = (int)(totalSeconds / 60);
	int totalRemainder = (int)(totalSeconds % 60);

	int currSeconds = int ((g_playback_status->currentPlaybackFrame + 123) / 60);
	int currMinutes = (int)(currSeconds / 60);
	int currRemainder = (int)(currSeconds % 60);
	// Position string (i.e. MM:SS)
	char endTime[5];
	sprintf(endTime, "%02d:%02d", totalMinutes, totalRemainder);
	char currTime[5];
	sprintf(currTime, "%02d:%02d", currMinutes, currRemainder);

	std::string time = std::string(currTime) + " / " + std::string(endTime);

	// Setup the slider and gauge min/max values
	int minValue = m_slider->GetMin();
	int maxValue = m_slider->GetMax();
	if (maxValue != (int)g_playback_status->latestFrame || minValue != -123)
	{
		m_slider->SetRange(-123, (int)(g_playback_status->latestFrame));
	}

	// Only update values while not actively seeking
	if (g_playback_status->targetFrameNum == INT_MAX && m_slider->isDraggingSlider == false)
	{
		m_text->SetLabel(_(time));
		m_slider->SetValue(g_playback_status->currentPlaybackFrame);
	}
}
