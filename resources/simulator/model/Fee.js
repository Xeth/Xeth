var FeeSimulator = Backbone.Collection.extend({

    estimate:function(from, to, amount, factor){
        var gas = 25867;
        console.log(factor);
        var price = 0.0000000002*factor;
		return {gas:gas, price:price, fee:(gas*price).toFixed(13)};
    },

    estimateCreateProfile:function(context, id, feeFactor){
		return this.estimate(null, null, 2, feeFactor);
    },
    
    estimateEditProfile:function(uri, details, feeFactor){
		return this.estimate(null, null, 3, feeFactor);
    },

    estimateMoveProfile:function(uri, context, id, feeFactor){
		return this.estimate(null, null, 4, feeFactor);
    },

    estimateStealthLink:function(uri, stealth, feeFactor){
		return this.estimate(null, null, 5, feeFactor);
    }
});
