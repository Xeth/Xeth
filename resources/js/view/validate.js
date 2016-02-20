

(function ( $ ) {
    $.fn.error = function(){
        $(this).focus(function(){$(this).parent().removeClass("error")}).parent().addClass("error");
    }
    $.fn.validate = function(callback) {
        var result = true;
        this.each(function(){
            var input = $(this);
            if(!input.val().length){
                input.error();
                if(callback!=undefined){
                    callback(input);
                }
                result = false;
            }
        });
        return result;
    };
 
}( jQuery ));
