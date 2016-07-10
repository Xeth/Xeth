function FileSystem(){
    this.browse = function(){
        console.log("browsing...");
        return "somefile"+Math.random();

    }
    this.readImage = function(){
        return Math.random();
    }
    return this;
}
