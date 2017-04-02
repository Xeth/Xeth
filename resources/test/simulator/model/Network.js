var NetworkSimulator = Backbone.Model.extend({

    initialize:function(){
        this.fetch();
    },

    fetch:function(peers){
        this.set("peers", peers||8);
    },

    observe:function(callback){
        var self = this;
        var callback = function(){
            setTimeout(function(){
                self.updateAsync(callback);
            }, 5000);
        };
        self.updateAsync(callback);
    },

    updateAsync:function(callback){
        this.fetch();
        if(callback!=undefined) callback(this.get("peers"));
    }

});

