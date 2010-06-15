import Qt 4.6

Rectangle{
	id: stage
	color: "#00000000"
	
	width: 128
	height: 128

	Image {
		id: reticle
		source: "dev/reticle.svg"
		anchors.horizontalCenter: stage.horizontalCenter
		anchors.verticalCenter: stage.verticalCenter

		width: 128
		height: 128

		transformOrigin: Item.Center
		rotation: 0
/*		rotation: SequentialAnimation{
			running: true
			repeat: true
			NumberAnimation{ to: 1080; easing: "easeLinear"; duration: 10000 }
		}*/
	}


}
