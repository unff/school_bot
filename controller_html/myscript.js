$.ajaxSetup({timeout:100});

var latch = false;

function readUrlAV (form) {
    TextVar = form.inputbox.value;
	VideoVar = "http://"+TextVar+":8080/video";
	AudioVar = "http://"+TextVar+":8080/audio.opus";
	document.getElementById("video").setAttribute('data', VideoVar);
	document.getElementById("audio").setAttribute('data', AudioVar);
}
function testarArduino (form) {
    TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "cm3": 7000 })	;
	{Connection: close};
}

document.onkeydown = checkKeyDown;
document.onkeyup = checkKeyUp;

function checkKeyDown(e) {

    e = e || window.event;

    if (e.keyCode == '38') {
        // up arrow
		if (latch == false) {
			console.log('up arrow begin: '+Date.now().tostring)
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm1": 1000 })	;
			{Connection: close};
			console.log('up arrow end: '+Date.now().tostring)
			latch = true;
		}
    }
    else if (e.keyCode == '40') {
        // down arrow
		if (latch == false) {
			console.log('down arrow sent: '+Date.now().tostring)
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm2": 1000 })	;
			{Connection: close};
			console.log('down arrow end: '+Date.now().tostring)
			latch = true;
		}
    }
    else if (e.keyCode == '37') {
       // left arrow
	   if (latch == false) {
			console.log('left arrow sent: '+Date.now().tostring)
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm3": 1000 })	;
			{Connection: close};
			console.log('left arrow end: '+Date.now().tostring)
			latch = true;
		}

	}
    else if (e.keyCode == '39') {
       // right arrow
	   if (latch == false) {
			console.log('right arrow sent: '+Date.now().tostring)
			TextVar = myform2.inputbox.value;
			ArduinoVar = "http://" + TextVar + ":80";
			$.get( ArduinoVar, { "cm4": 1000 })	;
			{Connection: close};
			console.log('right arrow end: '+Date.now().tostring)
			latch = true;
		}
	}
}

function checkKeyUp(e) {
    e = e || window.event;

    if ((e.keyCode == '38')||(e.keyCode == '40')||(e.keyCode == '37')||(e.keyCode == '39')) {
        // up arrow
		setTimeout(doNothing, 500);
    }
}

function doNothing(){
	console.log('reset sent: '+Date.now().tostring)
	TextVar = myform2.inputbox.value;
	ArduinoVar = "http://" + TextVar + ":80";
	$.get( ArduinoVar, { "cm5": 1000 })	;
	{Connection: close};
	console.log('reset end: '+Date.now().tostring)
	latch = false;
}
