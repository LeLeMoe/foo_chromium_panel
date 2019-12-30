let fb2k = new class fb2k {
    static PostRequest = class {
        #post_url = "http://2B2BE8EB-336D-4E5B-9BA3-000D7BC6B097";
        #xml_request = new XMLHttpRequest();
        constructor() {
            this.#xml_request.open("POST", this.#post_url, false);
            this.#xml_request.setRequestHeader("Content-Type","text/plain");
        }
        post(data) {
            this.#xml_request.send(JSON.stringify(data));
            return { ready_state : this.#xml_request.readyState, status : this.#xml_request.status, response : this.#xml_request.responseText };
        }
    };
    // API
    play_control = new class {
        play() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00000 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        pause() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00001 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        play_or_pause() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00002 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        stop() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00003 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        next() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00004 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        previous() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00005 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        set_now_time(time) {
            if(typeof(value) != "number") {
                return { status: "fail", detail: "wrong type of parameters" };
            }
            let respond = request.post({ cmd: 0x00006, time: time });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        get_total_time() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00007 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        get_now_time() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00008 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
    };
    volume_control = new class {
        up() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00100 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        down() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00101 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        mute() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00102 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        set_volume(value) {
            if(typeof(value) != "number") {
                return { status: "fail", detail: "wrong type of parameters" };
            }
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00103, volume: value });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
        get_volume() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00104 });
            let respond_json = JSON.parse(respond.response);
            if(respond.ready_state == 4 && respond.status == 200) {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
    };
    playlist_manager = new class {
        get_playlist_count() {
            let request = new fb2k.PostRequest();
            let respond = request.post({ cmd: 0x00200 });
            let respond_json = JSON.parse(respond.response);
            if (respond.ready_state == 4 && respond.status == 200 && respond_json.status == "success") {
                return respond_json;
            } else {
                return { status: "fail", detail: "communicate error" };
            }
        }
    }
};