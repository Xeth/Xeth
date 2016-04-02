var EventListener = function(){

    var contextCallbacks = {};
    var callbacks = [];

    var emitError = function(error){
        for(var i in callbacks)
        {
            callbacks[i](error.message);
        }
        if(error.context)
        {
            var handlers = contextCallbacks[error.context];
            if(Array.isArray(handlers))
            {
                for(var i in handlers)
                {
                    handlers[i](error.message, error.uri);
                }
            }
        }
    };

    this.listen = function(){
        XETH_event.Error.connect(this, emitError);
    };

    this.onError = function(context, callback){
        if(!callback)
        {
            callbacks.push(context);
        }
        else
        {
            if(contextCallbacks[context]==undefined) contextCallbacks[context] = [];
            contextCallbacks[context].push(callback);
        }
    };

}
