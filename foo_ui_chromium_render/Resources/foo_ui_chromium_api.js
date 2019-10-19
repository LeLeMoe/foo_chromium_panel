let fb2k = new class {
    // Post class
    PostRequest = class {
        #post_url = "2B2BE8EB-336D-4E5B-9BA3-000D7BC6B097";
        #xml_request = new XMLHttpRequest();
        constructor() {
            this.xml_request.open("POST", this.#post_url, false);
            this.xml_request.setRequestHeader("Content-type","application/json");
        }
        post(data) {
            this.xml_request.send(JSON.stringify(data));
            return { readyState : this.xml_request.readyState, status : this.xml_request.status, response : this.xml_request.responseText };
        }
    };
    // API
    play_control = new class {
        play() {
            alert("666");
        }
    };
};