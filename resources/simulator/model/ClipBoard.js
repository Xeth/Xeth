function ClipBoard(){
    var data;
    this.copyText = function(txt){
        data = txt;
    }
    this.getText = function(){
        return data;
    }
}
