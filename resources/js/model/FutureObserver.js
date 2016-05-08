function FutureObserver(future){
    this.future = future;
}

FutureObserver.prototype.onFinished = function(callback){

    var future = this.future;

    future.Finished.connect(function(){
        callback(future.getResult());
    });

    if(future.isFinished()){
        setTimeout(callback, 0, future.getResult());
    }
}


