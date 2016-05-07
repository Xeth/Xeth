function FutureObserver(future){
    this.future = future;
}

FutureObserver.prototype.onFinished = function(callback){
    this.future.Finished.connect(callback);
    if(this.future.isFinished()){
        setTimeout(callback, 0);
    }
}


