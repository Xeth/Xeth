function ClipBoard(){
    var data;
    this.setText = function(txt){
        data = txt;
        return true;
    }
    this.getText = function(){
        return data;
    }
}
