var EventListener = function(){

    var dataCallbacks = {callbacks:[], contextCallbacks:[]};
    var errorCallbacks = {callbacks:[], contextCallbacks:[]};

    var emitEvent = function(event, container){
        for(var i in container.callbacks)
        {
            container.callbacks[i](event);
        }
        if(event.context)
        {
            var handlers = container.contextCallbacks[event.context];
            if(Array.isArray(handlers))
            {
                for(var i in handlers)
                {
                    handlers[i](event);
                }
            }
        }
    };

    var emitError = function(event){
        emitEvent(event, errorCallbacks);
    };

    var emitData = function(event){
        emitEvent(event, dataCallbacks);
    };

    var saveCallback = function(container, context, callback){
        if(!callback)
        {
            container.callbacks.push(context);
        }
        else
        {
            if(container.contextCallbacks[context]==undefined) container.contextCallbacks[context] = [];
            container.contextCallbacks[context].push(callback);
        }
    };

    this.listen = function(){
        XETH_event.Error.connect(this, emitError);
        XETH_event.Data.connect(this, emitData);
    };

    this.onError = function(context, callback){
        saveCallback(errorCallbacks, context, callback);
    };

    this.onData = function(context, callback){
        saveCallback(dataCallbacks, context, callback);
    };
}
