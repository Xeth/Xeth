function FileSystem(){
    this.browse = function(){
        console.log("browsing...");
        return "somefile"+Math.random();
    }
    return this;
}
