let fb2k = new class fb2k {
    static PostRequest = class {
        #post_url = "http://2B2BE8EB-336D-4E5B-9BA3-000D7BC6B097";
        #xml_request = new XMLHttpRequest();
        constructor() {
            this.#xml_request.open("POST", this.#post_url, false);
            this.#xml_request.setRequestHeader("Content-Type","application/json");
        }
        post(data) {
            alert(JSON.stringify(data));
            this.#xml_request.send(JSON.stringify(data));
            return { readyState : this.xml_request.readyState, status : this.xml_request.status, response : this.xml_request.responseText };
        }
    };
    // API
    play_control = new class {
        play() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.play_control.play" });
            if(respond.readyState == 4 && respond.status == 200) {
                alert("successful");
                return true;
            } else {
                alert("failed");
                return false;
            }
        }
        pause() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.play_control.pause" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        play_or_pause() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.play_control.play_or_pause" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        stop() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.play_control.stop" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        next() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.play_control.next" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        previous() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.play_control.previous" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
    };
    volume_control = new class {
        up() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.volume_control.up" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        down() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.volume_control.down" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        mute() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.volume_control.mute" });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        set(value) {
            if(typeof(value) != "number") {
                return false;
            }
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.volume_control.set", volume : value });
            if(respond.readyState == 4 && respond.status == 200) {
                return true;
            } else {
                return false;
            }
        }
        get() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd : "fb2k.volume_control.get" });
            if(respond.readyState == 4 && respond.status == 200) {
                return JSON.parse(respond.response).volume;
            } else {
                return -1;
            }
        }
    };
};