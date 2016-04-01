var FeeSimulator = Backbone.Collection.extend({

    estimate:function(from, to, amount, factor){
		return {gas:200, price:0.01, fee:"2"};
    },

    estimateCreateProfile:function(from, to, amount, factor){
		return {gas:300, price:0.01, fee:"3"};
    },
    
    estimateEditProfile:function(from, to, amount, factor){
		return {gas:400, price:0.01, fee:"4"};
    },

    estimateMoveProfile:function(from, to, amount, factor){
		return {gas:500, price:0.01, fee:"5"};
    }
});
