let fb2k = class {
    /*
     * fb2k.play()
     * Continue to play 
     * Parameter: none
     * Return: none
     */
    play() {
        window.cefQuery({
            request: "F13CF149-39C1-4B1B-885D-68E86D29FD2A",
            persistent: false,
            onSuccess: function (response) { },
            onFailure: function (error_code, error_message) { }
        });
    }
    /*
     * fb2k.pause()
     * Stop to play music
     * Parameter: none
     * Return: none
     */
    pause() {
        window.cefQuery({
            request: "BC3A82F4-EA0A-4F9A-8AE7-0AF4541F0D3E",
            persistent: false,
            onSuccess: function (response) { },
            onFailure: function (error_code, error_message) { }
        });
    }
    /*
     * fb2k.next()
     * Play next music
     * Parameter: none
     * Return: none
     */
    next() {
        window.cefQuery({
            request: "63AC1132-34FC-4517-84FF-99831C1E4963",
            persistent: false,
            onSuccess: function (response) { },
            onFailure: function (error_code, error_message) { }
        });
    }
    /*
     * fb2k.previous()
     * Play previous music
     * Parameter: none
     * Return: none
     */
    previous() {
        window.cefQuery({
            request: "134BB381-3242-49CA-AF95-A408614EE829",
            persistent: false,
            onSuccess: function (response) { },
            onFailure: function (error_code, error_message) { }
        });
    }
};