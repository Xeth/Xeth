function ClipBoard(){
    var data;
    this.setText = function(txt){
        data = txt;
    }
    this.getText = function(){
        return data;
    }
}
