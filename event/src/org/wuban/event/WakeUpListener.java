package org.wuban.event;

public class WakeUpListener implements EventListener {
 	
	private EventObject event;
	
	public WakeUpListener(EventObject ev)
	{
		this.event = ev;
	}

	@Override
	public void performed(){
		this.event.process();
	}
	
}
