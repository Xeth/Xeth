var Network = Backbone.Model.extend({

    fetch:function(){
        this.set("peers", XETH_network.getPeersCount());
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
        var self = this;
        var future = new FutureObserver(XETH_network.getPeersCountAsync());
        future.onFinished(function(peers){
            self.set("peers", peers);
            if(callback!=undefined) callback(peers);
        });
    }

});

