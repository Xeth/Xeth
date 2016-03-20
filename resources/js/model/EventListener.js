var EventListener = function(){

    this.onError = function(callback){
        XETH_event.Error.connect(this, callback);
    };

}
