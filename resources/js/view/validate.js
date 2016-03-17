

(function ( $ ) {
    $.fn.error = function(){
        $(this).focus(function(){$(this).noerror()}).closest(".section_mandatory").addClass("error");
    };
    $.fn.noerror = function(){
        $(this).closest(".section_mandatory").removeClass("error");
    };
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
			else input.noerror();
        });
        return result;
    };
 
}( jQuery ));
